// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetAnimationInterface.h"
#include "UObject/Object.h"
#include "UserWidget/Base/UserWidgetInterface.h"
#include "WidgetAnimationEvent.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew)
class SCREENWIDGETGENERATION_API UWidgetAnimationEvent : public UObject, public IWidgetAnimationInterface
{
	GENERATED_BODY()

	/* IWidgetAnimationInterface */
public:
	virtual void NativeOnOpen(UUserWidgetBase* InUserWidget) override;
	virtual void NativeOnClose(UUserWidgetBase* InUserWidget) override;

public:
	FSimpleMulticastDelegate GetOnAnimationFinishDelegate() { return OnAnimationFinish; }

public:
	UFUNCTION(BlueprintCallable)
	void RequestAnimationFinish();

protected:
	FSimpleMulticastDelegate OnAnimationFinish;
};
