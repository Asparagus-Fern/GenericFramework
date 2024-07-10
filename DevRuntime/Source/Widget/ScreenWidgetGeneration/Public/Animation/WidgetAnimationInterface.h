// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetAnimationInterface.generated.h"

class UWidgetAnimationEvent;

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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HasAnimationEvent() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UWidgetAnimationEvent* GetAnimationEvent() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAnimationEvent(UWidgetAnimationEvent* InAnimationEvent);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayAnimationEvent(bool InIsActive);


};
