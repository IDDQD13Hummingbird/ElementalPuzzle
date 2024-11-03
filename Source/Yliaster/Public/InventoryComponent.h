// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
using namespace std;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "stack"
#include "MyElement.h"
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

<<<<<<< HEAD
<<<<<<< HEAD

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	TArray<AMyElement*> InventoryStack;
=======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	TArray<UItem*> InventoryStack;
>>>>>>> fbe3984 (Fixed syntax)
=======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	TArray<AMyElement*> InventoryStack;
>>>>>>> fb142f1 (Updated MyChar to comply with new Tile delegate)

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	int32 Capacity;


	// FUNCTIONS


	bool AddItem(AMyElement* Item);
	bool RemoveItem(AMyElement* Item);




};
