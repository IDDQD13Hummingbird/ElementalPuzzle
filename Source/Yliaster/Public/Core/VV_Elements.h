// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VV_Elements.generated.h"

class UTexture2D;



UENUM(BlueprintType)
enum class EVV_ElementType : uint8
{
	Void = 0		UMETA(Hidden),
	Fire = 1		UMETA(DisplayName = "Fire"),
	Air = 2			UMETA(DisplayName = "Air"),
	Lightning = 3	UMETA(DisplayName = "Lightning"),
	Water = 4		UMETA(DisplayName = "Water"),
	Steam = 5		UMETA(DisplayName = "Steam"),
	Ice = 6			UMETA(DisplayName = "Ice"),
	Earth = 7		UMETA(DisplayName = "Earth"),
	Metal = 8		UMETA(DisplayName = "Metal"),
	Dust = 9		UMETA(DisplayName = "Dust"),
	Fate = 10		UMETA(Hidden),
	Wood = 11		UMETA(DisplayName = "Wood"),
};

USTRUCT(BlueprintType)
struct YLIASTER_API FVV_ElementData : public FDataTableRowHandle
{
	GENERATED_BODY()

	
	TSharedPtr<UTexture2D> Icon;
};

/**
 * 
 */