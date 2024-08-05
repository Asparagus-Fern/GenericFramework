// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/CommonObject.h"
#include "Procedure/ProcedureInterface.h"
#include "UObject/Object.h"
#include "WidgetAnimationEvent.generated.h"

class UWidget;
/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class SCREENWIDGETGENERATION_API UWidgetAnimationEvent : public UCommonObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayAnimation(UWidget* TargetWidget);
};
