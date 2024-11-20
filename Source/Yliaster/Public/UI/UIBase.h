// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

class UCanvasPanel;
class UHorizontalBox;
class UNamedSlot;
class UVVElementIcon;


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

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI")
	UNamedSlot* WidgetDisplay;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI")
	UHorizontalBox* InventorySlot;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* InventorySpacer;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI")
	UNamedSlot* ActiveSlot;

	UPROPERTY(EditAnywhere, Category = "Assets")
	TArray<UTexture2D*> ElementVisuals;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UVVElementIcon> ElementDisplayClass;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	UVVElementIcon* AddElement(int32 ElementIndex);

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 RemoveElement();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ReplaceElement(int32 ElementIndex);

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget* DisplayWidget(TSubclassOf<UUserWidget> WidgetToDisplay);
};
