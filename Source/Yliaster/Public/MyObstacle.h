// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyElement.h"
#include "InteractionInterface.h"
#include "MyObstacle.generated.h"

UCLASS()
class YLIASTER_API AMyObstacle : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	FString RequiredElement;

//	UFUNCTION()
//	void ElementInteract(AMyElement* OtherActor);
};
