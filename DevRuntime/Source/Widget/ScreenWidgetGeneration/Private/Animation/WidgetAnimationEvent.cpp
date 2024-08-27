// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WidgetAnimationEvent.h"

#include "ScreenWidgetType.h"

void UWidgetAnimationEvent::PlayAnimation_Implementation()
{
	/* todo:如果在游戏的第一帧使用DoTween操作动画的过渡(所有，包括UI动画)，将会失效，必须在OnWorldMatchStarting之后才有效 */
}

void UWidgetAnimationEvent::NativePlayAnimation(UWidget* InTargetWidget)
{
	TargetWidget = InTargetWidget;
	PlayAnimation();
}
