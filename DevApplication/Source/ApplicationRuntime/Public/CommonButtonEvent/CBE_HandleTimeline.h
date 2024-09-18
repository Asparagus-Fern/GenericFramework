// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBTweenBase.h"
#include "DBTweenFloat.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleTimeline.generated.h"

class UTimelineButtonEvent;

/**
 * 处理时间轴类型按钮事件
 */
UCLASS(MinimalAPI)
class UCBE_HandleTimeline : public UCommonButtonEvent
{
	GENERATED_BODY()

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	/* 过渡时间 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 0.f;

	/* 过渡曲线类型 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EaseType EaseType = EaseType::Linear;

	/* 是否循环 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsLoop = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UTimelineButtonEvent* TimelineEvent;

protected:
	UPROPERTY()
	UDBTweenFloat* DBTweenFloat;

	/* 当时间轴过渡时 */
	UFUNCTION()
	virtual void OnHandleUpdate(float Alpha);

	/* 当时间轴完成时 */
	UFUNCTION()
	virtual void OnHandleFinish(float Alpha);
};
