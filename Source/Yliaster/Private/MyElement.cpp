// Fill out your copyright notice in the Description page of Project Settings.


#include "MyElement.h"

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
	AMyElement Fire;
	Fire.ElementType = "Fire";

	AMyElement Water;
	Water.ElementType = "Water";
	
}

//Called every frame
void AMyElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
