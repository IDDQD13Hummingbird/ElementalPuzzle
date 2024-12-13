// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VV_TileData.generated.h"


USTRUCT()
struct FVV_TileData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Grid")
	bool bVisibleByDefault = true;

	UPROPERTY(EditAnywhere, Category = "Grid")
	float HoveredThickness = 4;
	UPROPERTY(EditAnywhere, Category = "Grid")
	float NeighborThickness = 2;
	UPROPERTY(EditAnywhere, Category = "Grid")
	float UnselectedThickness = 0.5;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FColor DefaultColor = FColor::White;
};