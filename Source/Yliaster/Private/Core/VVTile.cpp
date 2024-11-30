// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVTile.h"



UVVTile::UVVTile()
{
	this->bHiddenInGame = false;
	this->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->Adjacents.SetNum(4);
}

void UVVTile::BeginPlay()
{
	Super::BeginPlay();

	this->OnBeginCursorOver.AddDynamic(this, &UVVTile::OnCursorOverlapBegin);
	this->OnEndCursorOver.AddDynamic(this, &UVVTile::OnCursorOverlapEnd);
	this->OnClicked.AddDynamic(this, &UVVTile::OnCursorClicked);
}

void UVVTile::OnCursorOverlapBegin(UPrimitiveComponent* TouchedComponent)
{
	SetLineThickness(5);

	for (UVVTile* AdjacentTile : Adjacents)
	{
		if (AdjacentTile == nullptr)
			continue;

		AdjacentTile->SetLineThickness(3);
	}
}

void UVVTile::OnCursorOverlapEnd(UPrimitiveComponent* TouchedComponent)
{
	SetLineThickness(1);

	for (UVVTile* AdjacentTile : Adjacents)
	{
		if (AdjacentTile == nullptr)
			continue;

		AdjacentTile->SetLineThickness(1);
	}
}

void UVVTile::OnCursorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, FString::Printf(TEXT("Coordinates are X: %i, Y: %i, and cost is %i"), XCoordinate, YCoordinate, TraversalCost));
	}
	TileClickDelegate.Broadcast(this, XCoordinate, YCoordinate, ButtonPressed);
}

