// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVGate.h"
#include "Core/VVGridActorComponent.h"
#include "Core/Player/VVUIComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/VVGateDisplayWidget.h"
#include "UI/UIBase.h"

AVVGate::AVVGate()
{
	if (!InWorldDisplay)
	{
		InWorldDisplay = CreateDefaultSubobject<UWidgetComponent>(FName("Key Display"));
		InWorldDisplay->SetupAttachment(GridConnection);
	}
}

void AVVGate::RecreateWidget()
{
	if (UVVGateDisplayWidget* DisplayWidget = Cast<UVVGateDisplayWidget>(InWorldDisplay->GetWidget()))
	{
		DisplayWidget->ClearSequence();
		for (EVVElementType KeyN : KeySequence)
		{
			DisplayWidget->AddKey(KeyN);
		}
	}
}

void AVVGate::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	RecreateWidget();
}

void AVVGate::BeginPlay()
{
	Super::BeginPlay();

	RecreateWidget();
}

void AVVGate::Interact(APawn* InteractingPlayer)
{
	UUIBase* CurrentPlayerUI;

	if (UVVUIComponent* UIConnection = InteractingPlayer->GetComponentByClass<UVVUIComponent>())
		CurrentPlayerUI = UIConnection->GetUIBase();
	else
		return;


	while (KeySequence.Num())
	{
		if (CurrentPlayerUI->CheckElement() == KeySequence.Last(0))
		{
			CurrentPlayerUI->RemoveElement();
			KeySequence.Pop();

			if (UVVGateDisplayWidget* DisplayWidget = Cast<UVVGateDisplayWidget>(InWorldDisplay->GetWidget()))
			{
				DisplayWidget->RemoveKey();
			}
		}
		else
			return;
	}

	Open();
}

#if WITH_EDITOR
void AVVGate::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	RecreateWidget();
}
#endif

void AVVGate::Open()
{
	GridConnection->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetActorLocation(GetActorLocation() - FVector(0, 0, 100), true);
}
