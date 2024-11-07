// Fill out your copyright notice in the Description page of Project Settings.


#include "MyElement.h"
#include "InventoryComponent.h"
// Sets default values
AMyElement::AMyElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	//OtherInventoryRef->AddItem(this);
	Destroy();
}

