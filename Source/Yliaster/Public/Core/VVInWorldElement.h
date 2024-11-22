// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Core/VVElementData.h"
#include "VVInWorldElement.generated.h"

class UWidgetComponent;

UCLASS()
class YLIASTER_API AVVInWorldElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVVInWorldElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (RowType = "VVElement"))
	FDataTableRowHandle ElementData;

	UPROPERTY(EditAnywhere, Category = "Element")
	UBoxComponent* PickupRange;

	UPROPERTY(EditAnywhere, Category = "Element")
	EVVElementType CurrentElementType;

	UPROPERTY(EditAnywhere, Category = "Element")
	UWidgetComponent* ElementVisual;

	UFUNCTION()
	void OnRangeEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Element")
	void SetElement(EVVElementType ElementType);

};
