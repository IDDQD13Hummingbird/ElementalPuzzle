// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "InventoryComponent.h"
#include "Core/VVGrid.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating the Root component
	CharRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	RootComponent = CharRoot;

	// Creating the Mesh component
	CharMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CharMesh->SetupAttachment(RootComponent);

	InventoryReference = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	//Inventory->Capacity = 5;

	Target = CreateDefaultSubobject<UBoxComponent>(TEXT("Target"));

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetActorLocation();


}

FVector AMyCharacter::GetCharLocation()
{

	return FVector();
}

//void AMyCharacter::MoveCharacter() 
//{
//	BaseMoveSpeed = 20.0f;
//
//}

