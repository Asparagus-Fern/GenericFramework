// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleTimeline.h"

#include "DBTweenFloat.h"
#include "CommonButtonEvent/TimelineButtonEvent/TimelineButtonEvent.h"

bool UCBE_HandleTimeline::CanExecuteButtonEvent_Implementation()
{
	return IsValid(TimelineEvent) && TimelineEvent->CanExecuteButtonEvent();
}

void UCBE_HandleTimeline::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	DBTweenFloat = UDBTweenFloat::DOFloat("", Duration, 0.f, 1.f, EaseType, bIsLoop);
	DBTweenFloat->OnUpdate.AddDynamic(this, &UCBE_HandleTimeline::OnHandleUpdate);
	DBTweenFloat->OnComplete.AddDynamic(this, &UCBE_HandleTimeline::OnHandleFinish);
}

void UCBE_HandleTimeline::OnHandleUpdate(float Alpha)
{
	ITimelineButtonEventInterface::Execute_HandleTimelineUpdate(TimelineEvent, Alpha);
}

void UCBE_HandleTimeline::OnHandleFinish(float Alpha)
{
	ITimelineButtonEventInterface::Execute_HandleTimelineFinish(TimelineEvent, Alpha);

	DBTweenFloat->OnUpdate.RemoveAll(this);
	DBTweenFloat->OnComplete.RemoveAll(this);
	DBTweenFloat = nullptr;

	if (bIsAsync)
	{
		MarkAsActivedFinish();
	}
}
