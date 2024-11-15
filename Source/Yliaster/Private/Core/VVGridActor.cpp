// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVGridActor.h"
#include "Core/VVGridActorComponent.h"


// Sets default values
AVVGridActor::AVVGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridConnection = CreateDefaultSubobject<UVVGridActorComponent>(FName("GridConnection"));
	GridConnection->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AVVGridActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (GridConnection)
		GridConnection->ShouldInteractDelegate.BindDynamic(this, &AVVGridActor::Interact);

}

// Called every frame
void AVVGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVVGridActor::Interact(APawn* InteractingPlayer)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, FString::Printf(TEXT("Interaction Triggered")));
	}
}

