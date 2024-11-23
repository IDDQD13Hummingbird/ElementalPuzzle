// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VVGateDisplayWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "UI/VVElementIcon.h"

EVVElementType UVVGateDisplayWidget::RemoveKey()
{
	EVVElementType RemovedElement = EVVElementType::Null;

	int32 KeyCount = KeyDisplay->GetChildrenCount();
	if (KeyCount > 0)
	{
		UVVElementIcon* RemovedWidget = Cast<UVVElementIcon>(KeyDisplay->GetChildAt(KeyCount - 1));
		RemovedElement = RemovedWidget->ElementType;

		RemovedWidget->RemoveFromParent();
	}
	return RemovedElement;
}

void UVVGateDisplayWidget::AddKey(EVVElementType NewKey)
{
	if (WidgetClass && NewKey != EVVElementType::Null)
	{
		FVVElement* NewElementData = ElementData.DataTable->FindRow<FVVElement>(FName(UEnum::GetDisplayValueAsText(NewKey).ToString()), "");

		UVVElementIcon* NewKeyWidget = CreateWidget<UVVElementIcon>(this, WidgetClass);
		NewKeyWidget->SetVisual(NewElementData->Icon);
		NewKeyWidget->ElementType = NewKey;
		UHorizontalBoxSlot* WidgetProperty = KeyDisplay->AddChildToHorizontalBox(NewKeyWidget);

		WidgetProperty->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		WidgetProperty->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

		FSlateChildSize SizeProperty;
		SizeProperty.Value = 1;
		SizeProperty.SizeRule = ESlateSizeRule::Fill;

		WidgetProperty->SetSize(SizeProperty);
	}
}

EVVElementType UVVGateDisplayWidget::CheckKey()
{
	EVVElementType CurrentKey = EVVElementType::Null;

	int32 KeyCount = KeyDisplay->GetChildrenCount();
	if (KeyCount)
	{
		UVVElementIcon* CurrentKeyWidget = Cast<UVVElementIcon>(KeyDisplay->GetChildAt(KeyCount - 1));
		CurrentKey = CurrentKeyWidget->ElementType;
	}

	return CurrentKey;
}

void UVVGateDisplayWidget::ClearSequence()
{
	KeyDisplay->ClearChildren();
}
