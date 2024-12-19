// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_GameModeBase.h"

AActor* AVV_GameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* PotentialSpawn = Super::ChoosePlayerStart(Player);

	return PotentialSpawn;
}
