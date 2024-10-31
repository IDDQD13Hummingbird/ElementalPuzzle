// Fill out your copyright notice in the Description page of Project Settings.


#include "MyChar.h"
#include "InventoryComponent.h"
#include "Core/VVGrid.h"
#include "Core/VVTile.h"

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

	Target = CreateDefaultSubobject<UBoxComponent>(TEXT("Target"));

}

// Called when the game starts or when spawned
void AMyChar::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyChar::InteractOnOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AMyChar::InteractEnd);

	

}

// Called every frame
void AMyChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentDistance < TotalDistance) {
		FVector Location = GetActorLocation();
		Location += Direction * BaseMoveSpeed * DeltaTime;
		SetActorLocation(Location);
		CurrentDistance = (Location - StartLocation).Size();
	}

}

FVector AMyChar::GetCharLocation()
{

	return FVector();
}

void AMyChar::InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Overlapping"));
	Interface = Cast<IInteractionInterface>(OtherActor);
	if (!GridReference) {
		GridReference = Cast<AVVGrid>(OtherActor);
		if (GridReference) {
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("function called"));
			GridReference->TileClickedDelegate.AddDynamic(this, &AMyChar::GridDetectionTest);
		}
	}
	
	/*TileReference = Cast<UVVTile>(OtherComponent);
	if (TileReference) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("function called"));
		TileReference->TileClickDelegate.AddDynamic(this, &AMyChar::GridDetectionTest);
	}*/
}

void AMyChar::InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Stopped Overlapping"));
	Interface = nullptr;
}

void AMyChar::InteractOnInput()
{
	if (Interface)
	{
		Interface->InteractWithThis(); //calls the function of the same name in the object it interacts with
	}
}

void AMyChar::GridDetectionTest(UVVTile* FetchedTileReference, int32 X, int32 Y)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Grid Detected"));
	StartLocation = GetActorLocation();
	Direction = FetchedTileReference->GetComponentLocation() - StartLocation;
	TotalDistance = Direction.Size();

	Direction = Direction.GetSafeNormal();
	CurrentDistance = 0.0f;

	/*if (FetchedTileReference) {
		if (CurrentDistance < TotalDistance) {
			FVector Location = GetActorLocation();
			Location += Direction * BaseMoveSpeed;
			SetActorLocation(Location);
			CurrentDistance = (Location - StartLocation).Size();
		}
	}*/
	

}

// Called to bind functionality to input
void AMyChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

