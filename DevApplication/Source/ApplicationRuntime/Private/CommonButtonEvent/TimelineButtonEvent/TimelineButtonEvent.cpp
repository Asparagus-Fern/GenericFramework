// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/TimelineButtonEvent/TimelineButtonEvent.h"

#include "CommonButtonEvent/CBE_HandleTimeline.h"

UTimelineButtonEvent::UTimelineButtonEvent()
{
	if (Cast<UCBE_HandleTimeline>(GetOuter()))
	{
		bIsTimeline = true;
	}
	else
	{
		bIsTimeline = false;
	}
}

bool UTimelineButtonEvent::CanExecuteButtonEvent_Implementation()
{
	return Super::CanExecuteButtonEvent_Implementation();
}

void UTimelineButtonEvent::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();
}

void UTimelineButtonEvent::HandleTimelineUpdate_Implementation(float Alpha)
{
	ITimelineButtonEventInterface::HandleTimelineUpdate_Implementation(Alpha);
}

void UTimelineButtonEvent::HandleTimelineFinish_Implementation(float Alpha)
{
	ITimelineButtonEventInterface::HandleTimelineFinish_Implementation(Alpha);
}
