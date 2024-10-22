// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
using namespace std;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "stack"
#include "Item.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YLIASTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// COMPONENTS

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	stack<UItem*> InventoryStack;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	int32 Capacity;


	// FUNCTIONS


	bool AddItem(UItem* Item);
	bool RemoveItem(UItem* Item);


};
