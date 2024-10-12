// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class YLIASTER_API AVVPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	AVVPlayerController();

public:
	virtual void BeginPlay() override;
};
