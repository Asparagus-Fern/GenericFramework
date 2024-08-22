// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBTweenBase.h"
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
	void PlayAnimation();
	void NativePlayAnimation(UWidget* InTargetWidget);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLoop = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float Duration = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EaseType EaseType = EaseType::Linear;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidget* TargetWidget;
};
