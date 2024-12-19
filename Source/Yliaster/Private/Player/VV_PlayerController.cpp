// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VV_PlayerController.h"

AVV_PlayerController::AVV_PlayerController()
{
	bEnableClickEvents = 1;
	bEnableMouseOverEvents = 1;
	DefaultClickTraceChannel = ECollisionChannel::ECC_Visibility;
}

void AVV_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
}
