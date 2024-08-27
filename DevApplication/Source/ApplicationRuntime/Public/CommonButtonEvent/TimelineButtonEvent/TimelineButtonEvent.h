// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBTweenBase.h"
#include "DBTweenFloat.h"
#include "TimelineButtonEventInterface.h"
#include "Event/CommonButtonEvent.h"
#include "TimelineButtonEvent.generated.h"

/**
 * 时间轴类型按钮事件，重写ITimelineButtonEventInterface的函数进行过渡处理
 */
UCLASS(Abstract)
class APPLICATIONRUNTIME_API UTimelineButtonEvent : public UCommonButtonEvent, public ITimelineButtonEventInterface
{
	GENERATED_BODY()

public:
	UTimelineButtonEvent();

	/* UCommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

	/* ITimelineButtonEventInterface */
public:
	virtual void HandleTimelineUpdate_Implementation(float Alpha) override;
	virtual void HandleTimelineFinish_Implementation(float Alpha) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bIsTimeline = false;
};
