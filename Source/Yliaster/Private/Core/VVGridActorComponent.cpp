// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVGridActorComponent.h"
#include "Core/VVGrid.h"
#include "Core/VVTile.h"

UVVGridActorComponent::UVVGridActorComponent()
{
	CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	CostModifier = 0;
	bShouldInteract = false;
	CurrentGrid = nullptr;
	InteractingPlayer = nullptr;
}

void UVVGridActorComponent::InitializeTiles()
{
	TArray<UPrimitiveComponent*> OverlappedComponents;
	GetOverlappingComponents(OverlappedComponents);
	for (UPrimitiveComponent* Component : OverlappedComponents)
	{
		if (UVVTile* TileComponent = Cast<UVVTile>(Component))
			ModifyTile(TileComponent);
	}

	if (!CurrentGrid)
	{
		TArray<AActor*> OverlappedActors;
		GetOverlappingActors(OverlappedActors, TSubclassOf<AVVGrid>());
		for (AActor* ActorN : OverlappedActors)
		{
			if (AVVGrid* NewGrid = Cast<AVVGrid>(ActorN))
			{
				CurrentGrid = NewGrid;
				CurrentGrid->TileClickedDelegate.AddDynamic(this, &UVVGridActorComponent::GridClicked);
				break;
			}
		}
	}
}

void UVVGridActorComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UVVTile* OverlappedTile = Cast<UVVTile>(OtherComp))
		ModifyTile(OverlappedTile);

	if (AVVGrid* NewGrid = Cast<AVVGrid>(OtherActor))
	{
		if (NewGrid != CurrentGrid)
		{
			CurrentGrid = NewGrid;
		}
	}

	if (APawn* OtherPawn = Cast<APawn>(OtherActor))
		InteractingPlayer = OtherPawn;

	if (bShouldInteract && InteractingPlayer)
	{
		ShouldInteractDelegate.ExecuteIfBound(InteractingPlayer);
		bShouldInteract = false;
	}
}

void UVVGridActorComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UVVTile* OverlappedTile = Cast<UVVTile>(OtherComp))
		RevertTile(OverlappedTile);

	InteractingPlayer = nullptr;
}


// Called when any intersecting tile is clicked
void UVVGridActorComponent::TileClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed)
{
	ObjectClickedDelegate.Broadcast(ButtonPressed);

	if (InteractingPlayer)
	{
		ShouldInteractDelegate.ExecuteIfBound(InteractingPlayer);
	}
	else
	{
		bShouldInteract = true;
	}
}

// Called when any tile on the grid is clicked
void UVVGridActorComponent::GridClicked(UVVTile* TileClicked, int32 X, int32 Y, FKey ButtonPressed)
{
	bShouldInteract = false;
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

	GetOwner()->GetWorldTimerManager().SetTimer(InitDelay, this, &UVVGridActorComponent::InitializeTiles, 0.1f, false);
}

void UVVGridActorComponent::SetCost(int32 NewCost)
{
	CostModifier = NewCost;
}
