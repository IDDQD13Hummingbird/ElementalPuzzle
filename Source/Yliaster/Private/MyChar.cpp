// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyChar.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InventoryComponent.h"
#include "Core/VVGrid.h"
#include "Core/VVTile.h"
#include "UI/UIBase.h"
#include "Core/Player/VVUIComponent.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
AMyChar::AMyChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating the Root component
	CharRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	CharRoot->SetupAttachment(RootComponent);

	// Creating the interaction box and attaching it to the character's mesh
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);

	// Creating the Mesh component
	CharMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CharMesh->SetupAttachment(RootComponent);

	InventoryReference = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	//Inventory->Capacity = 5;

	// This was originally supposed to be for testing the movement, but is now used as a second interaction box
	Target = CreateDefaultSubobject<UBoxComponent>(TEXT("Target"));

	UIComponentReference = CreateDefaultSubobject<UVVUIComponent>(TEXT("UI Component Reference"));

}

// Called when the game starts or when spawned
void AMyChar::BeginPlay()
{
	Super::BeginPlay();

	// Adding the Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
	
	// Declaring overlap dynamics
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyChar::CheckGrid);
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyChar::InteractOnOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AMyChar::InteractEnd);

	Interface = nullptr;

}

// Called every frame
void AMyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetTile.IsEmpty())
	{
		// How far the character has moved from the previous tile towards the next target tile
		// 0 = just set off, 1 = Reached the target
		MovementDelta += DeltaTime * BaseMoveSpeed;
		SetActorLocation(FMath::Lerp(CurrentTile->GetComponentLocation(), TargetTile[0]->GetComponentLocation(), MovementDelta));

		// If we've reached the target tile we move on to the next
		if (MovementDelta >= 1)
		{
			MovementDelta = 0;
			CurrentTile = TargetTile[0];
			TargetTile.RemoveAt(0);
		}
	}
}

FVector AMyChar::GetCharLocation()
{
	return FVector();
}

void AMyChar::CheckGrid(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GridReference) {
		GridReference = Cast<AVVGrid>(OtherActor);
		if (GridReference) {
#if WITH_EDITOR
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("function called")); // only visible in the editor
#endif
			GridReference->TileClickedDelegate.AddDynamic(this, &AMyChar::GridDetectionTest);
			GridRecievedDelegate.Broadcast();
		}
	}

	if (!CurrentTile)
	{
		if (UVVTile* TileReference = Cast<UVVTile>(OtherComponent))
			CurrentTile = TileReference;
	}
}

void AMyChar::InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interface = Cast<IInteractionInterface>(OtherActor);
	if (Interface) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Overlaps with item"));
		//Interface->InteractWithThis();
	}
}

void AMyChar::InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex)
{
	if (Cast<AMyElement>(OtherActor)) {
		//Interface = nullptr;
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Stopped Overlapping with item"));
	}
}

void AMyChar::InteractOnInput()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("interact action pressed"));
	if (Interface)
	{
		Interface->InteractWithThis(); //calls the function of the same name in the object it interacts with
	}
}

void AMyChar::TestInput()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("interact action pressed"));
}

void AMyChar::CallRemoveElement()
{
	if (SpawnedElementClass) {
		FVector PlayerLocation = GetActorLocation();
		FRotator PlayerRotation = GetActorRotation();
		UWorld* World = GetWorld();

		// Removes the element in the first spot in the element stack
		//UIComponentReference->GetUIBase()->RemoveElement();

		//pops the top element in the inventory and returns its element type
		EVVElementType ElementOfRemoved = UIComponentReference->GetUIBase()->RemoveElement(); 

		if (World && ElementOfRemoved != EVVElementType::Null) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Spawns he element at the player location
			AVVInWorldElement* SpawnedElement = World->SpawnActor<AVVInWorldElement>(SpawnedElementClass, PlayerLocation + FVector(0, 0, 150), PlayerRotation, SpawnParams);
			if (SpawnedElement) {
				SpawnedElement->SetElement(ElementOfRemoved); // Sets the element type to the type of the element we just popped
				SpawnedElement->bCanBePickedUp = false;
				SpawnedElement->SetActorLocation(PlayerLocation);
#if WITH_EDITOR
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Element was spawned")); // only visible in the editor
#endif
			}
		}
		
	}
	
}

void AMyChar::GridDetectionTest(UVVTile* FetchedTileReference, int32 X, int32 Y, FKey ButtonPressed)
{
	UVVTile* CurrentTarget = nullptr;
	// checks if the array of tiles is empty, then adds the current target to the queue
	if (!TargetTile.IsEmpty())
	{
		CurrentTarget = TargetTile[0];

		TargetTile.Empty();
		TargetTile.Add(CurrentTarget);
	}
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Grid Detected"));
	StartLocation = GetActorLocation();
	Direction = FetchedTileReference->GetComponentLocation() - StartLocation;
	TotalDistance = Direction.Size();

	Direction = Direction.GetSafeNormal();
	CurrentDistance = 0.0f;

	// Finds the optimal path to the target tile and moves the player along that path
	TargetTile.Append(GridReference->FindPath(CurrentTarget? CurrentTarget : CurrentTile, FetchedTileReference));
}

// Called to bind functionality to input
void AMyChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AMyChar::InteractOnInput);
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &AMyChar::TestInput);
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Completed, this, &AMyChar::CallRemoveElement);
	}

}

