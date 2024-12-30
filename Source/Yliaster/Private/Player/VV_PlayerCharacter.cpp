// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VV_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Player/VV_Camera.h"

// Sets default values
AVV_PlayerCharacter::AVV_PlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	if (!PlayerSprite)
	{
		PlayerSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Sprite"));
		RootComponent = PlayerSprite;
	}
	if (!InteractionRange)
	{
		InteractionRange = CreateDefaultSubobject<UBoxComponent>(FName("Reach"));
		InteractionRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		InteractionRange->SetupAttachment(RootComponent);
	}
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
		Camera->SetLocationRef(GetActorLocation());
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

void AVV_PlayerCharacter::SetGrid(AVV_Grid* NewGrid)
{
	ActiveGrid = NewGrid;
}

