// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Core/VV_Tile.h"
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
			FIntPoint TileCoord = FIntPoint(0);
			TArray<UVV_Tile*> PossibleStartingTiles = GridConnection->VerifyConnection();
			if (PossibleStartingTiles.Num() > 0)
			{
				int RandomIndex = FMath::Rand() % (PossibleStartingTiles.Num() - 1);
				TileCoord = PossibleStartingTiles[RandomIndex]->GetGridPosition();
			}

			if (AVV_PlayerController* PlayerRef = Cast<AVV_PlayerController>(Player))
			{
				PlayerRef->ActiveGrid = GridConnection->ConnectedGrid;
				PlayerRef->StartTile = TileCoord;
			}
			SelectedSpawn = SpawnRef;
		}
	}

	return SelectedSpawn;
}
