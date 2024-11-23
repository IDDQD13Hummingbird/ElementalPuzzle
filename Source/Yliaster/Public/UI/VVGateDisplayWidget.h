// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/VVElementData.h"
#include "VVGateDisplayWidget.generated.h"

	class UHorizontalBox;
	class UVVElementIcon;

/**
 * 
 */
UCLASS()
class YLIASTER_API UVVGateDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "VVElement"))
	FDataTableRowHandle ElementData;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category = "UI")
	UHorizontalBox* KeyDisplay;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UVVElementIcon> WidgetClass;

public:
	UFUNCTION(BlueprintCallable, Category = "Element")
	EVVElementType RemoveKey();

	UFUNCTION(BlueprintCallable, Category = "Element")
	void AddKey(EVVElementType NewKey);

	UFUNCTION(BlueprintCallable, Category = "Element")
	EVVElementType CheckKey();

	UFUNCTION(BlueprintCallable, Category = "Element")
	void ClearSequence();
};
