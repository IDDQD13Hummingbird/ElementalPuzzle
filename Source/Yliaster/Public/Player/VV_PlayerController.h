// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VV_PlayerController.generated.h"

class AVV_Grid;

/**
 * 
 */
UCLASS()
class YLIASTER_API AVV_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	AVV_PlayerController();

public:
	virtual void BeginPlay() override;

	UPROPERTY()
	AVV_Grid* ActiveGrid;
};
