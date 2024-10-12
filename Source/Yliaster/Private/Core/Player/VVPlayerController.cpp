// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/VVPlayerController.h"

AVVPlayerController::AVVPlayerController()
{
	bEnableClickEvents = 1;
	bEnableMouseOverEvents = 1;
}

void AVVPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
}
