// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "VVGridActorComponent.generated.h"

class UVVTile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileObjectClickedSignature, FKey, ButtonPressed);


/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class YLIASTER_API UVVGridActorComponent : public UBoxComponent
{
	GENERATED_BODY()
	
protected:
	UVVGridActorComponent();

	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 CostModifier;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void TileClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed);

	UFUNCTION()
	void ModifyTile(UVVTile* TargetTile);

	UFUNCTION()
	void RevertTile(UVVTile* TargetTile);


public:
	virtual void BeginPlay() override;

	FTileObjectClickedSignature ObjectClickedDelegate;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetCost(int32 NewCost);
};
