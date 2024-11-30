// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "VVGridActorComponent.generated.h"

class UVVTile;
class AVVGrid;
class IVVGridActorInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileObjectClickedSignature, FKey, ButtonPressed);
DECLARE_DYNAMIC_DELEGATE_OneParam(FCallInteractSignature, APawn*, InteractingPlayer);


/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class YLIASTER_API UVVGridActorComponent : public UBoxComponent
{
	GENERATED_BODY()
	
protected:
	UVVGridActorComponent();

	FTimerHandle InitDelay;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	virtual void InitializeTiles();

	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 CostModifier;

	UPROPERTY()
	AVVGrid* CurrentGrid;

	UPROPERTY()
	APawn* InteractingPlayer;

	UPROPERTY()
	bool bShouldInteract;



	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void TileClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed);
	
	UFUNCTION()
	void GridClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed);


	UFUNCTION()
	void ModifyTile(UVVTile* TargetTile);

	UFUNCTION()
	void RevertTile(UVVTile* TargetTile);


public:
	virtual void BeginPlay() override;

	FTileObjectClickedSignature ObjectClickedDelegate;
	FCallInteractSignature ShouldInteractDelegate;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetCost(int32 NewCost);
};
