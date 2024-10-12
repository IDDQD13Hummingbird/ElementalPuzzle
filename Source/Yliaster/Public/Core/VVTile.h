// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "VVTile.generated.h"

/**
 * 
 */
UCLASS()
class YLIASTER_API UVVTile : public UBoxComponent
{
	GENERATED_BODY()
protected:
	UVVTile();

	UFUNCTION(BlueprintCallable, Category = "Cursor")
	void OnCursorOverlapBegin(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Cursor")
	void OnCursorOverlapEnd(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Cursor")
	void OnCursorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	virtual void BeginPlay() override;

	// 0 = North, 1 = East, 2 = South, 3 = South
	UPROPERTY(EditAnywhere, Category = "Tile")
	TArray<UVVTile*> Adjacents;
	
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 Index;

	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 XCoordinate;
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 YCoordinate;
};
