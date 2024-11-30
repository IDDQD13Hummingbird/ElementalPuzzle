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

	if (RootComponent->GetNumChildrenComponents() != Columns * Rows)
	{
		PopulateGrid();
	}

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

void AVVGrid::OnTileClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed)
{
	TileClickedDelegate.Broadcast(TileClicked, X, Y, ButtonPressed);
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


	// Each Node Has it's Key(UVVTile*), Sum(Cost + Value) and Parent(UVVTile*) 
	struct TileNode
	{
		// The total cost of all tiles traversed
		int32 TotalCost;
		// TotalCost + ManhattenDistance
		int32 Value;
		UVVTile* Parent;
	};
	// Open list, Closed list, Add StartTile
	TMap<UVVTile*, TileNode> OpenTiles;
	TMap<UVVTile*, TileNode> ClosedTiles;

	OpenTiles.Add(StartTile, TileNode(0, ManhattenDistance(StartTile, EndTile), nullptr));

	UVVTile* CurrentTile{ nullptr };
	TileNode CurrentData{ 0, 0, nullptr };

	UVVTile* CurrentClosestTile{ StartTile };

	// While Open.Size() > 0
	while (!OpenTiles.IsEmpty())
	{
		//	Find Open with lowest Sum, Save as variable
		OpenTiles.ValueSort([](TileNode A, TileNode B) {return A.TotalCost + A.Value < B.TotalCost + B.Value; });
		for (TPair<UVVTile*, TileNode>& KeyValuePair : OpenTiles)
		{
			CurrentTile = KeyValuePair.Key;
			CurrentData = *OpenTiles.Find(CurrentTile);
			break;
		}

		if (CurrentTile == EndTile)
		{
			while (CurrentData.Parent)
			{
				Path.EmplaceAt(0, CurrentTile);

				UVVTile* CurrentParent = CurrentData.Parent;
				CurrentTile = CurrentParent;
				CurrentData = *ClosedTiles.Find(CurrentParent);
			}
			return Path;
		}

		if (ManhattenDistance(CurrentTile, EndTile) < ManhattenDistance(CurrentClosestTile, EndTile))
			CurrentClosestTile = CurrentTile;

		//	Remove Current from Open
		OpenTiles.Remove(CurrentTile);

		for (UVVTile* Adjacent : CurrentTile->Adjacents)
		{
			if (!Adjacent || Adjacent->TraversalCost < 0)
				continue;

			// Calculate Adjacent Sum
			int32 AdjacentCost = CurrentData.TotalCost + Adjacent->TraversalCost;
			int32 AdjacentValue = AdjacentCost + ManhattenDistance(Adjacent, EndTile);


			if (OpenTiles.Contains(Adjacent) && AdjacentValue > OpenTiles.Find(Adjacent)->Value)
				continue;
			if (ClosedTiles.Contains(Adjacent) && AdjacentValue > ClosedTiles.Find(Adjacent)->Value)
				continue;

			OpenTiles.Add(Adjacent, TileNode(AdjacentCost, AdjacentValue, CurrentTile));
		}

		ClosedTiles.Add(CurrentTile, CurrentData);
	}

	CurrentData = *ClosedTiles.Find(CurrentClosestTile);
	CurrentTile = CurrentClosestTile;
	while (CurrentData.Parent)
	{
		Path.EmplaceAt(0, CurrentTile);

		UVVTile* CurrentParent = CurrentData.Parent;
		CurrentTile = CurrentParent;
		CurrentData = *ClosedTiles.Find(CurrentParent);
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