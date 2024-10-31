// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "MyElement.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 5;
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(AMyElement* Item)
{
	InventoryStack.Push(Item);
	// WHY CAN I NOT PUSH THE ITEM INTO THE STACK?????? :(
	return false;
}

bool UInventoryComponent::RemoveItem(AMyElement* Item)
{
	InventoryStack.Pop();
	return false;
}

