// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnumComponent.generated.h"


const int FIRE = 0;
const int WATER = 1;

UENUM(BlueprintType)
enum class ElementType : uint8 {
	FIRE = 0 UMETA(DisplayName = "FIRE"),
	WATER = 1  UMETA(DisplayName = "WATER")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YLIASTER_API UEnumComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnumComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
