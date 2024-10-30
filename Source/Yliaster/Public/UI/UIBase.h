// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

class UCanvasPanel;

/**
 * 
 */
UCLASS()
class YLIASTER_API UUIBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* BaseCanvas;
};
