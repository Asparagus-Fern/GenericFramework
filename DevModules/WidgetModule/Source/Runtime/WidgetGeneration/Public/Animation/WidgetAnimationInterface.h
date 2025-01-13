// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetAnimationInterface.generated.h"

class UWidgetAnimation;

UINTERFACE(BlueprintType)
class UWidgetAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIDGETGENERATION_API IWidgetAnimationInterface
{
	GENERATED_BODY()

public:
	virtual bool HasWidgetAnimation(bool InIsActive) const { return false; }
	virtual UWidgetAnimation* GetActiveAnimation() const { return nullptr; }
	virtual UWidgetAnimation* GetInactiveAnimation() const { return nullptr; }
	virtual void PlayWidgetAnimation(bool InIsActive) { return; }
	virtual float GetWidgetAnimationDuration(bool InIsActive) { return 0.f; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void SetActiveAnimation(UWidgetAnimation* InAnimation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void SetInactiveAnimation(UWidgetAnimation* InAnimation);
};
