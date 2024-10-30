// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "InventoryComponent.h"
#include "Core/VVGrid.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//// Creating the Root component
	//CharRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	//RootComponent = CharRoot;

	//// Creating the interaction box and attaching it to the character's mesh
	//InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	//InteractionBox->SetupAttachment(CharMesh);

	//// Creating the Mesh component
	//CharMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//CharMesh->SetupAttachment(RootComponent);

	//InventoryReference = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	////Inventory->Capacity = 5;

	//Target = CreateDefaultSubobject<UBoxComponent>(TEXT("Target"));

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::InteractOnOverlap);
	//InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::InteractEnd);
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetActorLocation();


}
//
//FVector AMyCharacter::GetCharLocation()
//{
//
//	return FVector();
//}

//void AMyCharacter::InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Overlapping"));
//	Interface = Cast<IInteractionInterface>(OtherActor);
//}

//void AMyCharacter::InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Stopped Overlapping"));
//	Interface = nullptr;
//}

//void AMyCharacter::InteractOnInput()
//{
//	if (Interface)
//	{
//		Interface->InteractWithThis(); //calls the function of the same name in the object it interacts with
//	}
//}

//void AMyCharacter::MoveCharacter() 
//{
//	BaseMoveSpeed = 20.0f;
//
//}

//void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {}

