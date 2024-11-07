// Fill out your copyright notice in the Description page of Project Settings.
#include "MyObstacle.h"
#include "EnumComponent.h"
#include "InteractionInterface.h"

#pragma once





// Sets default values
AMyObstacle::AMyObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AMyObstacle::InteractWithThis()
//{
//	bool check = GetInventoryReference() == RequiredElement;
//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("InteractWithThis"));
//	if (check = true) {
//		InventoryReference.Pop();
//		Destroy;
//	};
//
//}  
