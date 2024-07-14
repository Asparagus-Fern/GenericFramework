// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleWorldWidgetPoint.generated.h"

/**
 * 处理3DUI点位的激活状态
 */
UCLASS()
class WORLDWIDGETGENERATION_API UCBE_HandleWorldWidgetPoint : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 激活时需要处理的3DUI状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Point"))
	TMap<FGameplayTag, bool> ActiveHandleWorldWidgetPointState;

	/* 不激活时需要处理的3DUI状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Point"))
	TMap<FGameplayTag, bool> InactiveHandleWorldWidgetPointState;
};
