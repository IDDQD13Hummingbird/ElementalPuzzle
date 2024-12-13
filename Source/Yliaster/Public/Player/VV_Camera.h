// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "VV_Camera.generated.h"

class AVV_Grid;

/**
 * 
 */
UCLASS()
class YLIASTER_API UVV_Camera : public UCameraComponent
{
	GENERATED_BODY()
	
protected:
	UVV_Camera();

	UPROPERTY()
	AVV_Grid* ActiveGrid;
	TSharedPtr<FVector> PlayerLocation;

	UPROPERTY()
	FVector GridMin;
	UPROPERTY()
	FVector GridMax;

	UPROPERTY()
	float MinX;
	UPROPERTY()
	float MaxX;
	UPROPERTY()
	float MinY;
	UPROPERTY()
	float MaxY;

	UPROPERTY()
	FVector GridExtent;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetActiveGrid(AVV_Grid* NewGrid);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetLocationRef(const FVector& InPlayerLocation);
};
