// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/VV_TileData.h"
#include "VV_Grid.generated.h"

class UVV_Tile;

UCLASS()
class YLIASTER_API AVV_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVV_Grid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVV_TileData TileData;

	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<UVV_Tile> TileClass;

	/* 
	The desired size of the grid:
	 X = Columns, Y = Rows
	*/
	UPROPERTY(EditAnywhere, Category = "Grid", meta = (ClampMin = "0"))
	FIntPoint GridSize = FIntPoint(10);

	UFUNCTION()
	void AssignAdjacents(UVV_Tile* TargetTile);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void OnTileClicked(UVV_Tile* TileClicked, FIntPoint Coordinates, FKey KeyPressed);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void RebuildGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FIntPoint CoordinateFromIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	int32 IndexFromCoordinate(FIntPoint Coordinate);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	FIntPoint GetGridSize() { return GridSize; }

	UFUNCTION(BlueprintCallable, Category = "Grid")
	UVV_Tile* GetTile(FIntPoint TileCoordinate);
};
