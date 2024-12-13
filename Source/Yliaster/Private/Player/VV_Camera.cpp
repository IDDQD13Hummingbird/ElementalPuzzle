// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VV_Camera.h"
#include "Core/VV_Grid.h"
#include "Core/VV_Tile.h"

UVV_Camera::UVV_Camera()
{
	ProjectionMode = ECameraProjectionMode::Orthographic;
}

void UVV_Camera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ActiveGrid && PlayerLocation)
	{
		SetWorldLocation(FVector(
			FMath::Clamp(PlayerLocation->X, MinX, MaxX),
			FMath::Clamp(PlayerLocation->Y, MinY, MaxY),
			PlayerLocation->Z ));
	}
}

void UVV_Camera::SetActiveGrid(AVV_Grid* NewGrid)
{
	ActiveGrid = NewGrid;
	if (!ActiveGrid)
		return;

	SetWorldRotation(ActiveGrid->GetTransform().GetRotation());

	FVector TileSize = ActiveGrid->GetTile(FIntPoint(0, 0))->GetScaledBoxExtent();

	GridMin = ActiveGrid->GetTile(FIntPoint(0, 0))->GetComponentLocation() - TileSize;
	GridMax = ActiveGrid->GetTile(ActiveGrid->GetGridSize() - FIntPoint(1, 1))->GetComponentLocation() + TileSize;

	GridExtent = (GridMax - GridMin) / 2;

	MinX = GridMin.X + GridExtent.X;
	MinY = GridMin.Y + GridExtent.Y;

	MaxX = GridMax.X - GridExtent.X;
	MaxY = GridMax.Y - GridExtent.Y;
}

void UVV_Camera::SetLocationRef(const FVector& InPlayerLocation)
{
	PlayerLocation = MakeShared<FVector>(InPlayerLocation);
}
