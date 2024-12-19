// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VV_GameModeBase.generated.h"

class AVV_Grid;
/**
 * 
 */
UCLASS()
class YLIASTER_API AVV_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

};
