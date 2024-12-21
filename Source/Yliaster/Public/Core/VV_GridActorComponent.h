// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "VV_GridActorComponent.generated.h"

class AVV_Grid;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YLIASTER_API UVV_GridActorComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVV_GridActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	// Negative values make affected Tiles untraversable
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 CostModifier = 1;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void VerifyConnection();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	AVV_Grid* ConnectedGrid;
	UPROPERTY()
	FIntPoint StartingCoords;
};
