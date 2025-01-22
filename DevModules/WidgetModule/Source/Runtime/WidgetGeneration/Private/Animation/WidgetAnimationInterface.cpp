// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WidgetAnimationInterface.h"

bool IWidgetAnimationInterface::HasWidgetAnimation(bool InIsActive) const
{
	return false;
}

bool IWidgetAnimationInterface::IsPlayingWidgetAnimation(bool InIsActive) const
{
	return false;
}

UWidgetAnimation* IWidgetAnimationInterface::GetActiveAnimation() const
{
	return nullptr;
}

UWidgetAnimation* IWidgetAnimationInterface::GetInactiveAnimation() const
{
	return nullptr;
}

void IWidgetAnimationInterface::PlayWidgetAnimation(bool InIsActive)
{
}

void IWidgetAnimationInterface::PlayWidgetAnimationRollback(bool InIsActive)
{
}

void IWidgetAnimationInterface::PauseWidgetAnimation(bool InIsActive)
{
}

void IWidgetAnimationInterface::StopWidgetAnimation(bool InIsActive)
{
}

float IWidgetAnimationInterface::GetWidgetAnimationDuration(bool InIsActive)
{
	return 0.f;
}
