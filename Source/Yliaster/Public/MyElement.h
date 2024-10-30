// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/VVGridActorComponent.h"
//#include "UObject/NoExportTypes.h"
#include "MyElement.generated.h"

UCLASS()
class YLIASTER_API AMyElement : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY()
	class UInventoryComponent* InventoryReference;
	virtual void Tick(float DeltaTime) override;
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	FString ElementType;
	//I wanted to use "Char", but Ureal was not on board with this decision.
	//Element type will be coded as "F" - fire, "W" - water, "A" - air, "E" - earth.
	//It is possible to go with "M" - metal, "I" - ice, "P" - plant, "L" - lighting


};
