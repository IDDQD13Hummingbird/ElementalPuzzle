// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VVGrid.generated.h"

class UVVTile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FTileClickedSignature, UVVTile*, TileClicked, int32, X, int32, Y, FKey, ButtonPressed);

USTRUCT()
struct FIntCoord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 X;
	UPROPERTY()
	int32 Y;
};


UCLASS()
class YLIASTER_API AVVGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVVGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Dimensions of the grid
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 Columns = 10;
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 Rows = 10;

	UPROPERTY(EditAnywhere, Category = "Grid")
	TSubclassOf<UVVTile> BaseTileClass;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void AssignNeighbors(UVVTile* Target);

public:	
	virtual void OnConstruction(const FTransform& Transform);

	FTileClickedSignature TileClickedDelegate;

	UFUNCTION()
	void OnTileClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey TilePressed);

	UFUNCTION()
	int32 IndexFromCoords(int32 X, int32 Y);
	UFUNCTION()
	FIntCoord CoordsFromIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	const int32 GetColumns() { return Columns; };
	UFUNCTION(BlueprintCallable, Category = "Grid")
	const int32 GetRows() { return Rows; };


	UFUNCTION(BlueprintCallable, Category = "Grid")
	UVVTile* GetTile(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void PopulateGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<UVVTile*> FindPath(UVVTile* StartTile, UVVTile* EndTile);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	int32 ManhattenDistance(UVVTile* TileA, UVVTile* TileB);
};
