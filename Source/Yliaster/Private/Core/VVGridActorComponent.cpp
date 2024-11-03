// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVGridActorComponent.h"
#include "Core/VVTile.h"

UVVGridActorComponent::UVVGridActorComponent()
{
	CostModifier = 0;
}

void UVVGridActorComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UVVTile* OverlappedTile = Cast<UVVTile>(OtherComp))
		ModifyTile(OverlappedTile);
}

void UVVGridActorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UVVTile* OverlappedTile = Cast<UVVTile>(OtherComp))
		RevertTile(OverlappedTile);
}

void UVVGridActorComponent::TileClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed)
{
	ObjectClickedDelegate.Broadcast(ButtonPressed);
}

void UVVGridActorComponent::ModifyTile(UVVTile* TargetTile)
{
	if (CostModifier < 0)
		TargetTile->TraversalCost *= -1;
	else
		TargetTile->TraversalCost += CostModifier;

	TargetTile->TileClickDelegate.AddDynamic(this, &UVVGridActorComponent::TileClicked);
}

void UVVGridActorComponent::RevertTile(UVVTile* TargetTile)
{
	if (CostModifier < 0)
		TargetTile->TraversalCost *= -1;
	else
		TargetTile->TraversalCost -= CostModifier;

	TargetTile->TileClickDelegate.RemoveDynamic(this, &UVVGridActorComponent::TileClicked);
}



void UVVGridActorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UVVGridActorComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UVVGridActorComponent::OnEndOverlap);

	TArray<UPrimitiveComponent*> OverlappedComponents;
	GetOverlappingComponents(OverlappedComponents);
	for (UPrimitiveComponent* Component : OverlappedComponents)
	{
		if (UVVTile* TileComponent = Cast<UVVTile>(Component))
			ModifyTile(TileComponent);
	}
}

void UVVGridActorComponent::SetCost(int32 NewCost)
{
	CostModifier = NewCost;
}
