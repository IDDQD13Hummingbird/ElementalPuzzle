// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VVElementIcon.h"
#include "Components/Image.h"

void UVVElementIcon::SetVisual(UTexture2D* NewImage)
{
	if (!BaseVisual)
		return;

	BaseVisual->SetBrushFromTexture(NewImage);
	BaseVisual->SetDesiredSizeOverride(FVector2D(80, 80));


}
