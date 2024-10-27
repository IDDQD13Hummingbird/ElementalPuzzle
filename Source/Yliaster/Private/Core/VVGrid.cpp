// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVGrid.h"
#include "Core/VVTile.h"

// Sets default values
AVVGrid::AVVGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("GridRoot"));
}

// Called when the game starts or when spawned
void AVVGrid::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> Tiles;
	RootComponent->GetChildrenComponents(false, Tiles);
	for (USceneComponent* var : Tiles)
	{
		if (UVVTile* Tile = Cast<UVVTile>(var))
			Tile->TileClickDelegate.AddDynamic(this, &AVVGrid::OnTileClicked);
	}
}


void AVVGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	if (!BaseTileClass)
		return;
	
	PopulateGrid();
}

void AVVGrid::OnTileClicked(UVVTile* TileClicked, int32 X, int32 Y)
{
	TileClickedDelegate.Broadcast(TileClicked, X, Y);
}

int32 AVVGrid::IndexFromCoords(int32 X, int32 Y)
{
	return X + Y * Columns;
}

FIntCoord AVVGrid::CoordsFromIndex(int32 Index)
{
	FIntCoord Output;
	Output.X = Index % Columns;
	Output.Y = Index / Columns;
	return Output;
}

UVVTile* AVVGrid::GetTile(int32 X, int32 Y)
{
	USceneComponent* UnverifiedTile = RootComponent->GetChildComponent(IndexFromCoords(X, Y));
	if (UVVTile* Tile = Cast<UVVTile>(UnverifiedTile))
	{
		return Tile;
	}
	return nullptr;
}

void AVVGrid::PopulateGrid()
{
	if (RootComponent->GetNumChildrenComponents() == Columns * Rows)
		return;

	TArray<USceneComponent*> Tiles;
	RootComponent->GetChildrenComponents(false, Tiles);
	for (USceneComponent* var : Tiles)
	{
		var->DestroyComponent();
	}

	FVector BoxSize = BaseTileClass->GetDefaultObject<UVVTile>()->GetScaledBoxExtent();
	float XOffset = 2 * BoxSize.X;
	float YOffset = 2 * BoxSize.Y;
	FVector CenterOffset = FVector(-BoxSize.X * Rows, -BoxSize.Y * Columns, 0);
	for (size_t i = 0; i < Rows; i++)
	{
		for (size_t j = 0; j < Columns; j++)
		{
			FTransform TargetLocation = FTransform(CenterOffset + FVector(i * XOffset, j * YOffset, 0));
			UVVTile* NewTile = NewObject<UVVTile>(this, BaseTileClass);
			if (NewTile)
			{
				NewTile->SetupAttachment(RootComponent);
				NewTile->SetRelativeTransform(TargetLocation);
				NewTile->RegisterComponent();

				NewTile->Index = i * Columns + j;
				NewTile->XCoordinate = i;
				NewTile->YCoordinate = j;
			}
		}
	}
	
	Tiles.Empty();
	RootComponent->GetChildrenComponents(false, Tiles);
	for (USceneComponent* var : Tiles)
	{
		if (UVVTile* Tile = Cast<UVVTile>(var))
			AssignNeighbors(Tile);
	}
}

TArray<UVVTile*> AVVGrid::FindPath(UVVTile* StartTile, UVVTile* EndTile)
{
	TArray<UVVTile*> Path;

	if (!StartTile->IsAttachedTo(RootComponent) || !EndTile->IsAttachedTo(RootComponent))
		return Path;

	struct TileNode
	{
		int32 TotalTraversed;
		int32 PathValue;
	};

	struct TileTree
	{
		UVVTile* Parent;
		TArray<UVVTile*> Children;
	};
	
	TMap<UVVTile*, UVVTile*> SearchedTiles;
	TMap<UVVTile*, TileNode> UnsearchedTiles;
	UVVTile* CurrentTile = nullptr;
	UnsearchedTiles.Add(StartTile, TileNode(0, ManhattenDistance(StartTile, EndTile)));

	int32 SearchCount = 0;
	while (SearchCount < Columns * Rows)
	{
		// Get the tile with the lowest cost (TotalTraversed + Manhattan)
		UnsearchedTiles.ValueSort([](TileNode A, TileNode B) {return A.PathValue < B.PathValue; });
		TArray<UVVTile*> KeyArray;
		UnsearchedTiles.GenerateKeyArray(KeyArray);
		// Add it to Searched, Set as Current and Remove it from Unsearched
		SearchedTiles.Add(KeyArray[0], CurrentTile);
		CurrentTile = KeyArray[0];
		UnsearchedTiles.FindAndRemoveChecked(CurrentTile);

		// If we reached the end tile
		if (CurrentTile == EndTile)
		{
			while (SearchedTiles.Find(CurrentTile))
			{
				Path.EmplaceAt(0, CurrentTile);
				CurrentTile = *SearchedTiles.Find(CurrentTile);

				return Path;
			}
		}
			
		// Add each traversable tile that is not in Searched to Unsearched
		for (UVVTile* Neighbor : CurrentTile->Adjacents)
		{
			TileNode* CurrentTileValues = UnsearchedTiles.Find(CurrentTile);
			if (Neighbor && Neighbor->TraversalCost >= 0 && !SearchedTiles.Contains(Neighbor))
			{
				int32 TraversedTotal = CurrentTileValues->PathValue + Neighbor->TraversalCost;
				UnsearchedTiles.Add(Neighbor, TileNode(TraversedTotal, TraversedTotal + CurrentTileValues->PathValue));
			}
		}

		SearchCount++;
	}
	return Path;
}

int32 AVVGrid::ManhattenDistance(UVVTile* TileA, UVVTile* TileB)
{
	return abs(TileB->XCoordinate - TileA->XCoordinate) + abs(TileB->YCoordinate - TileA->YCoordinate);
}


void AVVGrid::AssignNeighbors(UVVTile* Target)
{
	FIntCoord TargetCoord = CoordsFromIndex(Target->Index);
	// Search North
	if (TargetCoord.Y == Rows - 1)
		Target->Adjacents[0] = nullptr;
	else
		Target->Adjacents[0] = GetTile(TargetCoord.X, TargetCoord.Y + 1);

	// Search East
	if (TargetCoord.X == Columns - 1)
		Target->Adjacents[1] = nullptr;
	else
		Target->Adjacents[1] = GetTile(TargetCoord.X + 1, TargetCoord.Y);

	// Search South
	if (TargetCoord.Y == 0)
		Target->Adjacents[2] = nullptr;
	else
		Target->Adjacents[2] = GetTile(TargetCoord.X, TargetCoord.Y - 1);

	// Search West
	if (TargetCoord.X == 0)
		Target->Adjacents[3] = nullptr;
	else
		Target->Adjacents[3] = GetTile(TargetCoord.X - 1, TargetCoord.Y);
}