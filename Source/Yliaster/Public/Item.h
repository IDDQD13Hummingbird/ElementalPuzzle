// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class YLIASTER_API UItem : public UObject
{
	GENERATED_BODY()



public:

	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY()
	class UInventoryComponent* InventoryReference;
};
