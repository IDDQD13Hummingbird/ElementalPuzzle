// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/VVGridActor.h"
#include "Core/VVElementData.h"
#include "VVCombiner.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class YLIASTER_API AVVCombiner : public AVVGridActor
{
	GENERATED_BODY()
protected:
	AVVCombiner();

	UPROPERTY()
	EVVElementType ElementA;
	UPROPERTY()
	EVVElementType ElementB;

	UPROPERTY(EditAnywhere, meta = (RowType = "VVElement"))
	FDataTableRowHandle ElementData;

	UPROPERTY(EditAnywhere, Category = "UI")
	UWidgetComponent* ElementDisplay;

public:
	virtual void Interact(APawn* InteractingPlayer) override;
	
};
