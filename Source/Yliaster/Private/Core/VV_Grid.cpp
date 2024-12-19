// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_Grid.h"
#include "Core/VV_Tile.h"

// Sets default values
AVV_Grid::AVV_Grid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileData = FVV_TileData();

	if (!RootComponent)
		RootComponent = CreateDefaultSubobject<USceneComponent>(FName("GridRoot"));
}

// Called when the game starts or when spawned
void AVV_Grid::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVV_Grid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVV_Grid::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	if (this)
		RebuildGrid();
}

void AVV_Grid::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (this)
		RebuildGrid();
}


// Called when any tile is clicked
void AVV_Grid::OnTileClicked(UVV_Tile* TileClicked, FIntPoint Coordinates, FKey KeyPressed)
{
#if WITH_EDITOR
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, FString::Printf(TEXT("Coordinates of tile clicked are X: %i, Y: %i"), Coordinates.X, Coordinates.Y));
	}
#endif
}


void AVV_Grid::RebuildGrid()
{
	if (!GetWorld())
		return;


	TArray<USceneComponent*> Tiles;
	RootComponent->GetChildrenComponents(false, Tiles);

	if (!TileClass || Tiles.Num() == GridSize.X * GridSize.Y)
	{
		for (USceneComponent* Tile : Tiles)
		{
			if (UVV_Tile* OldTile = Cast<UVV_Tile>(Tile))
			{
				OldTile->SetTileData(TileData);
			}
		}
		return;
	}
	
	for (USceneComponent* Var : Tiles)
		Var->DestroyComponent();

	
	FVector TileSize = TileClass->GetDefaultObject<UVV_Tile>()->GetScaledBoxExtent();
	float XOffset = 2 * TileSize.X;
	float YOffset = 2 * TileSize.Y;
	FVector RootOffset = FVector(-TileSize.X * GridSize.Y, -TileSize.Y * GridSize.X, 0);

	for (size_t i = 0; i < GridSize.Y; i++)
	{
		for (size_t j = 0; j < GridSize.X; j++)
		{
			FTransform TargetLocation = FTransform(RootOffset + FVector(i * XOffset, j * YOffset, 0));
			UVV_Tile* NewTile = NewObject<UVV_Tile>(this, TileClass);
			if (NewTile)
			{
				NewTile->SetupAttachment(RootComponent);
				NewTile->SetRelativeTransform(TargetLocation);
				NewTile->SetTileData(TileData);
				NewTile->RegisterComponent();
				AddInstanceComponent(NewTile);

				NewTile->SetGridPosition(FIntPoint(j, i));

				NewTile->TileClickDelegate.BindDynamic(this, &AVV_Grid::OnTileClicked);
			}
		}
	}

	Tiles.Reset(GridSize.X * GridSize.Y);
	RootComponent->GetChildrenComponents(false, Tiles);
	for (USceneComponent* Var : Tiles)
	{
		if (UVV_Tile* Tile = Cast<UVV_Tile>(Var))
			AssignAdjacents(Tile);
	}
}

void AVV_Grid::AssignAdjacents(UVV_Tile* TargetTile)
{
	const FIntPoint TargetLocation = TargetTile->GetGridPosition();

	bool bIsLeftEdge = TargetLocation.X == 0;
	bool bIsRightEdge = TargetLocation.X == GridSize.X - 1;
	bool bIsTopEdge = TargetLocation.Y == GridSize.Y - 1;
	bool bIsBottomEdge = TargetLocation.Y == 0;

	TargetTile->Adjacents.Reserve(4 - bIsLeftEdge || bIsRightEdge ? 1 : 0 - bIsTopEdge || bIsBottomEdge ? 1 : 0);

	if (!bIsLeftEdge)
		TargetTile->Adjacents.Add(GetTile(TargetLocation + FIntPoint(-1, 0)));

	if (!bIsRightEdge)
		TargetTile->Adjacents.Add(GetTile(TargetLocation + FIntPoint(1, 0)));
		
	if (!bIsTopEdge)
		TargetTile->Adjacents.Add(GetTile(TargetLocation + FIntPoint(0, 1)));

	if (!bIsBottomEdge)
		TargetTile->Adjacents.Add(GetTile(TargetLocation + FIntPoint(0, -1)));
}


FIntPoint AVV_Grid::CoordinateFromIndex(int32 Index)
{
	FIntPoint Coordinate;
	Coordinate.X = Index % GridSize.X;
	Coordinate.Y = Index / GridSize.X;
	return Coordinate;
}

int32 AVV_Grid::IndexFromCoordinate(FIntPoint Coordinate)
{
	return Coordinate.X + Coordinate.Y * GridSize.X;
}

UVV_Tile* AVV_Grid::GetTile(FIntPoint TileCoordinate)
{
	USceneComponent* UncheckedTile = RootComponent->GetChildComponent(IndexFromCoordinate(TileCoordinate));
	if (UVV_Tile* Tile = Cast<UVV_Tile>(UncheckedTile))
		return Tile;

	return nullptr;
}

