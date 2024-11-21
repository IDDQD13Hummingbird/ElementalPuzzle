// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/NamedSlot.h"
#include "UI/VVElementIcon.h"

UVVElementIcon* UUIBase::AddElement(int32 ElementIndex)
{
	if (!ElementVisuals[ElementIndex] || !ElementDisplayClass)
		return nullptr;

	// If there is an active element move it to inventory
	if (ActiveSlot->GetContent())
	{
		UHorizontalBoxSlot* PanelProperties = InventorySlot->AddChildToHorizontalBox(ActiveSlot->GetContent());
		PanelProperties->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);
		FSlateChildSize SizeProperty;
		SizeProperty.Value = 1;
		SizeProperty.SizeRule = ESlateSizeRule::Automatic;
		PanelProperties->SetSize(SizeProperty);
	}

	UVVElementIcon* NewElement = CreateWidget<UVVElementIcon>(this, ElementDisplayClass);
	NewElement->SetVisual(ElementVisuals[ElementIndex]);
	NewElement->ElementIndex = ElementIndex;
	ActiveSlot->SetContent(NewElement);

    return NewElement;
}

int32 UUIBase::RemoveElement()
{
	if (!ActiveSlot->GetContent())
		return -1;

	UVVElementIcon* RemovedElement = Cast<UVVElementIcon>(ActiveSlot->GetContent());
	int32 RemovedElementIndex = RemovedElement->ElementIndex;


	int32 ElementCount = InventorySlot->GetChildrenCount();
	if (ElementCount > 1)
	{
		ActiveSlot->SetContent(InventorySlot->GetChildAt(ElementCount - 1));
	}
	else
	{
		ActiveSlot->SetContent(nullptr);
	}

	return RemovedElementIndex;
}

int32 UUIBase::CheckElement()
{
	if (!ActiveSlot->GetContent())
		return -1;
	
	UVVElementIcon* CurrentElement = Cast<UVVElementIcon>(ActiveSlot->GetContent());
	return CurrentElement->ElementIndex;
}

void UUIBase::ReplaceElement(int32 ElementIndex)
{
	if (!ElementVisuals[ElementIndex] || !ActiveSlot->GetContent())
		return;
	
	UVVElementIcon* CurrentElement = Cast<UVVElementIcon>(ActiveSlot->GetContent());
	CurrentElement->SetVisual(ElementVisuals[ElementIndex]);
}

UUserWidget* UUIBase::DisplayWidget(TSubclassOf<UUserWidget> WidgetToDisplay)
{
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(this, WidgetToDisplay);
	WidgetDisplay->SetContent(NewWidget);

	return NewWidget;
}
