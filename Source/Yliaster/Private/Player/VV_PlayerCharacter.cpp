// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VV_PlayerCharacter.h"
#include "Player/VV_Camera.h"

// Sets default values
AVV_PlayerCharacter::AVV_PlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!Camera)
	{
		Camera = CreateDefaultSubobject<UVV_Camera>(FName("Camera"));
	}
}

// Called when the game starts or when spawned
void AVV_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (ActiveGrid)
	{
		Camera->SetActiveGrid(ActiveGrid);
	}
}

// Called every frame
void AVV_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVV_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

