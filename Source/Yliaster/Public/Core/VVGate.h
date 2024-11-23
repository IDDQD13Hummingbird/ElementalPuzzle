// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/VVGridActor.h"
#include "Core/VVElementData.h"
#include "VVGate.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class YLIASTER_API AVVGate : public AVVGridActor
{
	GENERATED_BODY()

protected:
	AVVGate();

	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<EVVElementType> KeySequence;

	UPROPERTY(EditAnywhere, Category = "UI")
	UWidgetComponent* InWorldDisplay;

	UFUNCTION()
	void RecreateWidget();

	
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	virtual void Interact(APawn* InteractingPlayer) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, Category = "Door")
	void Open();
};
