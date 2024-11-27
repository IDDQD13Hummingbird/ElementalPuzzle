// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVCombiner.h"
#include "Core/VVGridActorComponent.h"
#include "Core/Player/VVUIComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/UIBase.h"
#include "UI/VVElementIcon.h"

AVVCombiner::AVVCombiner()
{
	ElementA = EVVElementType::Null;
	ElementB = EVVElementType::Null;

	if (!ElementDisplay)
	{
		ElementDisplay = CreateDefaultSubobject<UWidgetComponent>(FName("Element Display"));
		ElementDisplay->SetupAttachment(GridConnection);
		ElementDisplay->SetVisibility(false);
	}
}

void AVVCombiner::Interact(APawn* InteractingPlayer)
{
	UUIBase* CurrentUI;
	if (UVVUIComponent* UIHandler = InteractingPlayer->GetComponentByClass<UVVUIComponent>())
		CurrentUI = UIHandler->GetUIBase();
	else
		return;

	
	if (EVVElementType CurrentElement = CurrentUI->CheckElement(); CurrentElement != EVVElementType::Fire && CurrentElement != EVVElementType::Air && CurrentElement != EVVElementType::Water && CurrentElement != EVVElementType::Earth)
		return;


	if (ElementA == EVVElementType::Null)
	{
		ElementA = CurrentUI->RemoveElement();

		if (UVVElementIcon* CurrentDisplay = Cast<UVVElementIcon>(ElementDisplay->GetWidget()))
		{
			FVVElement* CurrentElement = ElementData.DataTable->FindRow<FVVElement>(FName(UEnum::GetDisplayValueAsText(ElementA).ToString()), "");
			CurrentDisplay->SetVisual(CurrentElement->Icon);
		}
		ElementDisplay->SetVisibility(true);
		return;
	}

	ElementB = CurrentUI->RemoveElement();

	uint8 ElementSum = (uint8)ElementA + (uint8)ElementB;
	CurrentUI->AddElement((EVVElementType)ElementSum);

	ElementA = EVVElementType::Null;
	ElementB = EVVElementType::Null;
	ElementDisplay->SetVisibility(false);
}
