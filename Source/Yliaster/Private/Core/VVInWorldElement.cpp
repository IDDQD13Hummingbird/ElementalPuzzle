// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVInWorldElement.h"
#include "Components/WidgetComponent.h"
#include "Core/Player/VVUIComponent.h"
#include "UI/UIBase.h"

// Sets default values
AVVInWorldElement::AVVInWorldElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!PickupRange)
	{
		PickupRange = CreateDefaultSubobject<UBoxComponent>(FName("Pickup Range"));
		PickupRange->SetupAttachment(RootComponent);
	}
	if (!ElementVisual)
	{
		ElementVisual = CreateDefaultSubobject<UWidgetComponent>(FName("Icon Display"));
		ElementVisual->SetupAttachment(PickupRange);
	}

}

// Called when the game starts or when spawned
void AVVInWorldElement::BeginPlay()
{
	Super::BeginPlay();

	if (PickupRange)
	{
		PickupRange->OnComponentBeginOverlap.AddDynamic(this, &AVVInWorldElement::OnRangeEntered);
	}
	
}

void AVVInWorldElement::OnRangeEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UVVUIComponent* TargetUIComponent = OtherActor->GetComponentByClass<UVVUIComponent>())
	{
		TargetUIComponent->GetUIBase()->AddElement(ElementType);
		Destroy();
	}
}

// Called every frame
void AVVInWorldElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVVInWorldElement::SetElement(int32 ElementIndex, UUserWidget* ElementIcon)
{
	if (!ElementVisual)
		return;

	ElementType = ElementIndex;
	ElementVisual->SetWidget(ElementIcon);
}

