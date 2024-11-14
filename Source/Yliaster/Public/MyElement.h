// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Core/VVGridActorComponent.h"
#include "Components/BoxComponent.h"

//#include "UObject/NoExportTypes.h"
#include "InteractionInterface.h"
#include "MyElement.generated.h"

const int FIRE = 0;
const int WATER = 1;

UENUM(BlueprintType)
enum class ElementType : uint8 {
	FIRE = 0 UMETA(DisplayName = "FIRE"),
    WATER = 1  UMETA(DisplayName = "WATER")
};
class UInventoryComponent;

UCLASS()
class YLIASTER_API AMyElement : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyElement();
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 CostModifier = 1;

	
	// COMPONENTS


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* CollisionBox;

	UInventoryComponent* OtherInventoryRef;

	UPROPERTY()
	class UInventoryComponent* InventoryReference;


	// FUNCTIONS


	virtual void Tick(float DeltaTime) override;
	// Called every frame, 


	//FString ElementType;
	//I wanted to use "Char", but Ureal was not on board with this decision.
	//Element type will be coded as "F" - fire, "W" - water, "A" - air, "E" - earth.
	//It is possible to go with "M" - metal, "I" - ice, "P" - plant, "L" - lighting

	//virtual void InteractWithThis() override;



	// Inherited via IInteractionInterface
	virtual void InteractWithThis() override;

};
