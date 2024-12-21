// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_GridActorComponent.h"
#include "Core/VV_Grid.h"
#include "Core/VV_Tile.h"

// Sets default values for this component's properties
UVV_GridActorComponent::UVV_GridActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVV_GridActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UVV_GridActorComponent::OnRegister()
{
	Super::OnRegister();

	VerifyConnection();
}

void UVV_GridActorComponent::VerifyConnection()
{
	TArray<UPrimitiveComponent*> OverlappedComponents;
	GetOverlappingComponents(OverlappedComponents);
	for (UPrimitiveComponent* Component : OverlappedComponents)
	{
		if (UVV_Tile* Tile = Cast<UVV_Tile>(Component))
		{
			Tile->RegisterTileActor(GetOwner(), CostModifier);
		}
		if (AVV_Grid* Grid = Cast<AVV_Grid>(Component->GetOwner()); Grid && (!ConnectedGrid || Grid != ConnectedGrid))
		{
			ConnectedGrid = Grid;
			Grid->OnRebuildDelegate.AddUniqueDynamic(this, &UVV_GridActorComponent::VerifyConnection);
		}
	}
}


// Called every frame
void UVV_GridActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

