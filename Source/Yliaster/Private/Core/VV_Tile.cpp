// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_Tile.h"
#include "Core/VV_TileData.h"


UVV_Tile::UVV_Tile()
{
	bHiddenInGame = false;

	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void UVV_Tile::SetTileData(const FVV_TileData& InData)
{
	SourceData = MakeShared<FVV_TileData>(InData);

	bHiddenInGame = !SourceData->bVisibleByDefault;
	SetLineThickness(SourceData->UnselectedThickness);
	ShapeColor = SourceData->DefaultColor;
}

// Cursor interactions

void UVV_Tile::OnCursorBeginOverlap(UPrimitiveComponent* TouchedComponent)
{
	if (!SourceData)
		return;

	if (!SourceData->bVisibleByDefault)
		bHiddenInGame = false;

	SetLineThickness(SourceData->HoveredThickness);
	for (UVV_Tile* AdjacentTile : Adjacents)
	{
		if (!SourceData->bVisibleByDefault)
			bHiddenInGame = false;

		if (AdjacentTile)
		AdjacentTile->SetLineThickness(SourceData->NeighborThickness);
	}
}

void UVV_Tile::OnCursorEndOverlap(UPrimitiveComponent* TouchedComponent)
{
	if (!SourceData)
		return;

	if (!SourceData->bVisibleByDefault)
		bHiddenInGame = true;

	SetLineThickness(SourceData->UnselectedThickness);
	for (UVV_Tile* AdjacentTile : Adjacents)
	{
		if (!SourceData->bVisibleByDefault)
			bHiddenInGame = false;

		if (AdjacentTile)
		AdjacentTile->SetLineThickness(SourceData->UnselectedThickness);
	}
}

void UVV_Tile::OnCursorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	TileClickDelegate.ExecuteIfBound(this, GridPosition, ButtonPressed);
}

void UVV_Tile::PostInitProperties()
{
	Super::PostInitProperties();

	OnBeginCursorOver.AddDynamic(this, &UVV_Tile::OnCursorBeginOverlap);
	OnEndCursorOver.AddDynamic(this, &UVV_Tile::OnCursorEndOverlap);
	OnClicked.AddDynamic(this, &UVV_Tile::OnCursorClicked);
}


void UVV_Tile::SetGridPosition(FIntPoint NewPosition)
{
	GridPosition = NewPosition;
}

FIntPoint UVV_Tile::GetGridPosition() const
{
	return GridPosition;
}
