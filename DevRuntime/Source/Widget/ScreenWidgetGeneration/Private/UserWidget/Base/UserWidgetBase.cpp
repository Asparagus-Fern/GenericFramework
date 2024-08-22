// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Base/UserWidgetBase.h"

#include "Animation/WidgetAnimationEvent.h"

UUserWidgetBase::UUserWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUserWidgetBase::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	IProcedureBaseInterface::Execute_OnCreate(this);

	SetIsActived(true);
}

void UUserWidgetBase::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	IProcedureBaseInterface::Execute_OnRefresh(this);
}

void UUserWidgetBase::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	IProcedureBaseInterface::Execute_OnDestroy(this);

	SetIsActived(false);
}

bool UUserWidgetBase::HasAnimationEvent_Implementation(const bool InIsActive) const
{
	return InIsActive ? IsValid(ActiveAnimationEvent) : IsValid(InactiveAnimationEvent);
}

UWidgetAnimationEvent* UUserWidgetBase::GetActiveAnimationEvent_Implementation() const
{
	return ActiveAnimationEvent;
}

void UUserWidgetBase::SetActiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent)
{
	IWidgetAnimationInterface::SetActiveAnimationEvent_Implementation(InAnimationEvent);
	ActiveAnimationEvent = InAnimationEvent;
}

UWidgetAnimationEvent* UUserWidgetBase::GetInactiveAnimationEvent_Implementation() const
{
	return InactiveAnimationEvent;
}

void UUserWidgetBase::SetInactiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent)
{
	IWidgetAnimationInterface::SetInactiveAnimationEvent_Implementation(InAnimationEvent);
	InactiveAnimationEvent = InAnimationEvent;
}

void UUserWidgetBase::PlayAnimationEvent_Implementation(bool InIsActive)
{
	IWidgetAnimationInterface::PlayAnimationEvent_Implementation(InIsActive);

	if (InIsActive)
	{
		if (IsValid(ActiveAnimationEvent))
		{
			ActiveAnimationEvent->NativePlayAnimation(this);
		}
	}
	else
	{
		if (IsValid(InactiveAnimationEvent))
		{
			InactiveAnimationEvent->NativePlayAnimation(this);
		}
	}
}

float UUserWidgetBase::GetAnimationDuration_Implementation(const bool InIsActive)
{
	IWidgetAnimationInterface::GetAnimationDuration_Implementation(InIsActive);

	if (InIsActive)
	{
		if (IsValid(ActiveAnimationEvent))
		{
			return ActiveAnimationEvent->Duration;
		}
	}
	else
	{
		if (IsValid(InactiveAnimationEvent))
		{
			return InactiveAnimationEvent->Duration;
		}
	}

	return 0.f;
}
