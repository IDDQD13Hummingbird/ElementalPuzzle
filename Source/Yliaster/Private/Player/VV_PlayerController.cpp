// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VV_PlayerController.h"
#include "Player/VV_PlayerCharacter.h"

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

void AVV_PlayerController::AcknowledgePossession(APawn* P)
{
	if (AVV_PlayerCharacter* PlayerCharacter = Cast<AVV_PlayerCharacter>(P); ActiveGrid && PlayerCharacter)
		PlayerCharacter->SetGrid(ActiveGrid);
}
