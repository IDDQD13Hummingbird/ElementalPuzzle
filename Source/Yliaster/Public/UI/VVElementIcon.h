// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VVElementIcon.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class YLIASTER_API UVVElementIcon : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI")
	UImage* BaseVisual;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetVisual(UTexture2D* NewImage);

	UPROPERTY(EditAnywhere, Category = "Element")
	int32 ElementIndex;
	
};
