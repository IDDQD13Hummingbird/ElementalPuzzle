// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VVUIComponent.generated.h"


class UUIBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YLIASTER_API UVVUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVVUIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUIBase> UIClass;

	UPROPERTY()
	UUIBase* UIBase;

	UPROPERTY()
	APlayerController* CurrentPlayer;

	UFUNCTION()
	void AssignController(APawn* Pawn, AController* OldController, AController* NewController);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* DisplayWidget(TSubclassOf<UUserWidget> WidgetToDisplay);
		
};
