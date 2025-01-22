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
	virtual bool HasWidgetAnimation(bool InIsActive) const;
	virtual bool IsPlayingWidgetAnimation(bool InIsActive) const;
	virtual UWidgetAnimation* GetActiveAnimation() const;
	virtual UWidgetAnimation* GetInactiveAnimation() const;
	virtual void PlayWidgetAnimation(bool InIsActive);
	virtual void PlayWidgetAnimationRollback(bool InIsActive);
	virtual void PauseWidgetAnimation(bool InIsActive);
	virtual void StopWidgetAnimation(bool InIsActive);
	virtual float GetWidgetAnimationDuration(bool InIsActive);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void SetActiveAnimation(UWidgetAnimation* InAnimation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void SetInactiveAnimation(UWidgetAnimation* InAnimation);
};
