// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VVUIGridActor.h"
#include "Core/Player/VVUIComponent.h"
#include "Blueprint/UserWidget.h"

void AVVUIGridActor::Interact(APawn* InteractingPlayer)
{
	if (!WidgetClass)
		return;

	if (UVVUIComponent* NewUIComponent = InteractingPlayer->GetComponentByClass<UVVUIComponent>())
	{
		CurrentUIComponent = NewUIComponent;
		CurrentUIInstance = CurrentUIComponent->DisplayWidget(WidgetClass);
	}
}
