// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VVElementData.generated.h"

class UTexture2D;

/**
 * 
 */
UENUM(BlueprintType)
enum class EVVElementType : uint8
{
	Null = 0		UMETA(Hidden),
	Fire = 1		UMETA(DisplayName = "Fire"),
	Air = 2			UMETA(DisplayName = "Air"),
	Lightning = 3	UMETA(DisplayName = "Lightning"),
	Water = 4		UMETA(DisplayName = "Water"),
	Steam = 5		UMETA(DisplayName = "Steam"),
	Ice = 6			UMETA(DisplayName = "Ice"),
	Earth = 7		UMETA(DisplayName = "Earth"),
	Metal = 8		UMETA(DisplayName = "Metal"),
	Dust = 9		UMETA(DisplayName = "Dust"),
	Wood = 11		UMETA(DisplayName = "Wood"),
};


USTRUCT(BlueprintType)
struct YLIASTER_API FVVElement : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EVVElementType Type;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
};
