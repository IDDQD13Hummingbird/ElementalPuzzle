// Fill out your copyright notice in the Description page of Project Settings.


#include "MyElement.h"
#include "InventoryComponent.h"
// Sets default values
AMyElement::AMyElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionBox;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(CollisionBox);

}

// Called when the game starts or when spawned
void AMyElement::BeginPlay()
{
	Super::BeginPlay();
	
}

//Called every frame
void AMyElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyElement::InteractWithThis()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Item has been interacted with"));
}

//void AMyElement::InteractWithThis()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Item has been interacted with"));
//	//OtherInventoryRef->AddItem(this);
//	//Destroy();
//}

