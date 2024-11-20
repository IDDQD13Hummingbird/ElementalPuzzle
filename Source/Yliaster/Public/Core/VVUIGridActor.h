// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/VVGridActor.h"
#include "VVUIGridActor.generated.h"

class UVVUIComponent;
class UUserWidget;

/**
 * 
 */
UCLASS()
class YLIASTER_API AVVUIGridActor : public AVVGridActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UVVUIComponent* CurrentUIComponent;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY()
	UUserWidget* CurrentUIInstance;

public:
	virtual void Interact(APawn* InteractingPlayer) override;
	
};
