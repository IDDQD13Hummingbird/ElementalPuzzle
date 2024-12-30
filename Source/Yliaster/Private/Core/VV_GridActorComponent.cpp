// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VV_GridActorComponent.h"
#include "Core/VV_Grid.h"
#include "Core/VV_Tile.h"

// Sets default values for this component's properties
UVV_GridActorComponent::UVV_GridActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	SetGenerateOverlapEvents(true);
}


// Called when the game starts
void UVV_GridActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnComponentBeginOverlap.AddDynamic(this, &UVV_GridActorComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UVV_GridActorComponent::OnOverlapEnd);
	
}

void UVV_GridActorComponent::OnRegister()
{
	Super::OnRegister();

	VerifyConnection();
}

void UVV_GridActorComponent::GridUpdate()
{
	AVV_Grid* OldGrid = ConnectedGrid;
	VerifyConnection();
	if (OldGrid && OldGrid != ConnectedGrid)
		OldGrid->OnRebuildDelegate.RemoveDynamic(this, &UVV_GridActorComponent::GridUpdate);
}

void UVV_GridActorComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UVV_Tile* InTile = Cast<UVV_Tile>(OverlappedComponent))
		InTile->RegisterTileActor(GetOwner(), CostModifier);
}

void UVV_GridActorComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UVV_Tile* OutTile = Cast<UVV_Tile>(OverlappedComponent))
		OutTile->UnregisterTileActor(GetOwner());
}

TArray<UVV_Tile*> UVV_GridActorComponent::VerifyConnection()
{
	UE_LOG(LogTemp, Display, TEXT("Verifying Grid connections..."));
	TArray<UVV_Tile*> ConnectedTiles;
	AVV_Grid* NewGrid = nullptr;

	TArray<UPrimitiveComponent*> OverlappedComponents;
	GetOverlappingComponents(OverlappedComponents);
	UE_LOG(LogTemp, Display, TEXT("Found %d possible Grid connections"), OverlappedComponents.Num());
	for (UPrimitiveComponent* Component : OverlappedComponents)
	{
		if (UVV_Tile* Tile = Cast<UVV_Tile>(Component))
		{
			Tile->RegisterTileActor(GetOwner(), CostModifier);
			ConnectedTiles.AddUnique(Tile);
		}
		if (AVV_Grid* Grid = Cast<AVV_Grid>(Component->GetOwner()); Grid && (!ConnectedGrid || Grid != ConnectedGrid))
		{
			NewGrid = Grid;
		}
	}

	if (NewGrid)
	{
		ConnectedGrid = NewGrid;
		ConnectedGrid->OnRebuildDelegate.AddUniqueDynamic(this, &UVV_GridActorComponent::GridUpdate);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("GridActor was unable to find a Grid"));
	return ConnectedTiles;
}


// Called every frame
void UVV_GridActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

