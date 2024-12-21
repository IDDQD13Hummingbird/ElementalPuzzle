// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "VV_Tile.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FTileClickedSignature, UVV_Tile*, TileClicked, FIntPoint, GridCoordinate, FKey, ButtonPressed);

struct FVV_TileData;

/**
 * 
 */
UCLASS()
class YLIASTER_API UVV_Tile : public UBoxComponent
{
	GENERATED_BODY()
protected:
	UVV_Tile();

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	FIntPoint GridPosition;

	TSharedPtr<FVV_TileData> SourceData;

	UPROPERTY()
	TMap<AActor*, int32> Modifiers;
	UFUNCTION()
	void UpdateModifier();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void OnCursorBeginOverlap(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Cursor")
	void OnCursorEndOverlap(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Cursor")
	void OnCursorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	
	
	// If negative then this tile is intraversible
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 TraversalCost = 0;

public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetTileData(const FVV_TileData& InData);

	UFUNCTION()
	void SetGridPosition(FIntPoint NewPosition);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FIntPoint GetGridPosition() const;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<UVV_Tile*> Adjacents;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void RegisterTileActor(AActor* TileActor, int32 Modifier);
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void UnregisterTileActor(AActor* TileActor);

	FTileClickedSignature TileClickDelegate;
};
