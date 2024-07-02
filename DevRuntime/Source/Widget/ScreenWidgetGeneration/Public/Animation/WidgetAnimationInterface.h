// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetAnimationInterface.generated.h"

class UUserWidgetBase;
// This class does not need to be modified.
UINTERFACE()
class UWidgetAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCREENWIDGETGENERATION_API IWidgetAnimationInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void OnOpen(UUserWidgetBase* InUserWidget);
	virtual void NativeOnOpen(UUserWidgetBase* InUserWidget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void OnClose(UUserWidgetBase* InUserWidget);
	virtual void NativeOnClose(UUserWidgetBase* InUserWidget);
};
