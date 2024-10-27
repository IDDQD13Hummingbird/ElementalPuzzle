// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/VVUIComponent.h"
#include "UI/UIBase.h"

// Sets default values for this component's properties
UVVUIComponent::UVVUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UVVUIComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!CurrentPlayer)
	{
		CurrentPlayer = GetOwner<APawn>()->GetController<APlayerController>();
	}

	// ...
	if (UIClass)
	{
		UIBase = CreateWidget<UUIBase>(CurrentPlayer, UIClass);
		if (UIBase)
			UIBase->AddToViewport();
	}
}


// Called every frame
void UVVUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

