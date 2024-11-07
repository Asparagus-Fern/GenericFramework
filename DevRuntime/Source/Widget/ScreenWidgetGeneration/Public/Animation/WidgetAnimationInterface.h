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
class SCREENWIDGETGENERATION_API IWidgetAnimationInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	bool HasActivationAnimation(bool InIsActive) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	UWidgetAnimation* GetActiveAnimation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void SetActiveAnimation(UWidgetAnimation* InAnimation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	UWidgetAnimation* GetInactiveAnimation() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void SetInactiveAnimation(UWidgetAnimation* InAnimation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	void PlayActivationAnimation(bool InIsActive);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Widget Animation Interface")
	float GetActivationAnimationDuration(bool InIsActive);
};
