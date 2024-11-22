// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/NamedSlot.h"
#include "UI/VVElementIcon.h"

UVVElementIcon* UUIBase::AddElement(EVVElementType ElementType)
{
	if (ElementData.IsNull())
		return nullptr;

	FVVElement* NewElementData = ElementData.DataTable->FindRow<FVVElement>(FName(UEnum::GetDisplayValueAsText(ElementType).ToString()), "");

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
	NewElement->SetVisual(NewElementData->Icon);
	NewElement->ElementType = NewElementData->Type;
	ActiveSlot->SetContent(NewElement);

    return NewElement;
}

EVVElementType UUIBase::RemoveElement()
{
	if (!ActiveSlot->GetContent())
		return EVVElementType::Null;

	UVVElementIcon* RemovedElement = Cast<UVVElementIcon>(ActiveSlot->GetContent());
	EVVElementType RemovedElementType = RemovedElement->ElementType;


	int32 ElementCount = InventorySlot->GetChildrenCount();
	if (ElementCount > 1)
	{
		ActiveSlot->SetContent(InventorySlot->GetChildAt(ElementCount - 1));
	}
	else
	{
		ActiveSlot->SetContent(nullptr);
	}

	return RemovedElementType;
}

EVVElementType UUIBase::CheckElement()
{
	if (!ActiveSlot->GetContent())
		return EVVElementType::Null;
	
	UVVElementIcon* CurrentElement = Cast<UVVElementIcon>(ActiveSlot->GetContent());
	return CurrentElement->ElementType;
}

void UUIBase::ReplaceElement(EVVElementType ElementType)
{
	if (ElementData.IsNull())
		return;
	
	FVVElement* NewElementData = ElementData.DataTable->FindRow<FVVElement>(FName(UEnum::GetDisplayValueAsText(ElementType).ToString()), "");

	UVVElementIcon* CurrentElement = Cast<UVVElementIcon>(ActiveSlot->GetContent());
	CurrentElement->SetVisual(NewElementData->Icon);
}

UUserWidget* UUIBase::DisplayWidget(TSubclassOf<UUserWidget> WidgetToDisplay)
{
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(this, WidgetToDisplay);
	WidgetDisplay->SetContent(NewWidget);

	return NewWidget;
}