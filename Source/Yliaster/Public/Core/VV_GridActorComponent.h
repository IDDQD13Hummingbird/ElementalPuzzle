// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "VV_GridActorComponent.generated.h"

class AVV_Grid;
class UVV_Tile;

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

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Grid")
	void GridUpdate();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	// Negative values make affected Tiles untraversable
	UPROPERTY(EditAnywhere, Category = "Grid")
	int32 CostModifier = 1;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	TArray<UVV_Tile*> VerifyConnection();

	UPROPERTY()
	AVV_Grid* ConnectedGrid;
	UPROPERTY()
	FIntPoint StartingCoords;
};
