// Fill out your copyright notice in the Description page of Project Settings.


// THIS CLASS IS UNUSED


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

#include "InteractionInterface.h"

#include "MyCharacter.generated.h"

UCLASS()
class YLIASTER_API AMyCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// COMPONENTS
	

	//Character's Mesh
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	//UStaticMeshComponent* CharMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	//UBoxComponent* InteractionBox;

	////Character's Root Component
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	//UCapsuleComponent* CharRoot;

	//// Target tile for character to move to
	//UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Component")
	//UBoxComponent* Target;
	//// USE GetComponentLocation for tracking target of the character

	//// Reference to inventory component
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	//class UInventoryComponent* InventoryReference;

	//IInteractionInterface* Interface = nullptr;


	//// VARIABLES

	//// Base movement speed of the coontrolled character
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	//float BaseMoveSpeed = 10.0f;


	//// FUNCTIONS


	////UFUNCTION()
	////void MoveCharacter();

	//UFUNCTION()
	//FVector GetCharLocation();

	//UFUNCTION()
	//void InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	//	int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	//	int32 OtherbodyIndex);

	//void InteractOnInput();

	//UFUNCTION()
	//void GridDetectionTest(UVVTile* TileReference, int32 X, int32 Y);

};

      