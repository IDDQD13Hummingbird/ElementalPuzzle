// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Core/VV_GridActorComponent.h"
#include "Player/VV_PlayerController.h"

AActor* AVV_GameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (!GetWorld())
		return nullptr;

	TArray<AActor*> PotentialSpawns;
	AActor* SelectedSpawn = nullptr;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PotentialSpawns);
	for (AActor* SpawnRef : PotentialSpawns)
	{
		if (UVV_GridActorComponent* GridConnection = SpawnRef->GetComponentByClass<UVV_GridActorComponent>())
		{
			if (AVV_PlayerController* PlayerRef = Cast<AVV_PlayerController>(Player))
			{
				PlayerRef->ActiveGrid = GridConnection->ConnectedGrid;
			}
			SelectedSpawn = SpawnRef;
		}
	}

	return SelectedSpawn;
}
