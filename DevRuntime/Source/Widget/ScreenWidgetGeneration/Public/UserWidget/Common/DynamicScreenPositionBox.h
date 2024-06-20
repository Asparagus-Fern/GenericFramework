// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "DynamicScreenPositionBox.generated.h"

class UCanvasPanel;

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UDynamicScreenPositionBox : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget = "CanvasPanel"))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UUserWidgetBase*> Widgets;
};
