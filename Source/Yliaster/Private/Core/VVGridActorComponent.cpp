// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVGridActorComponent.h"
#include "Core/VVTile.h"

void UVVGridActorComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UVVTile* OverlappedTile = Cast<UVVTile>(OtherComp))
	{
		if (CostModifier < 0)
			OverlappedTile->TraversalCost *= -1;
		else
			OverlappedTile->TraversalCost += CostModifier;
	}
}

void UVVGridActorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UVVTile* OverlappedTile = Cast<UVVTile>(OtherComp))
	{
		if (CostModifier < 0)
			OverlappedTile->TraversalCost *= -1;
		else
			OverlappedTile->TraversalCost -= CostModifier;
	}
}

void UVVGridActorComponent::TileClicked(UVVTile* TileClicked, int32 X, int32 Y)
{
}

void UVVGridActorComponent::BeginPlay()
{
	OnComponentBeginOverlap.AddDynamic(this, &UVVGridActorComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UVVGridActorComponent::OnEndOverlap);
}
