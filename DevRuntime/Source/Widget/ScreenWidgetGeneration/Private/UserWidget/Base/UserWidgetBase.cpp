// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Base/UserWidgetBase.h"

#include "Animation/WidgetAnimation.h"

UUserWidgetBase::UUserWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ActiveAnimation)
	{
		float A = ActiveAnimation->GetStartTime();
		float B = ActiveAnimation->GetEndTime();
	}
}

void UUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	FProperty* ActiveAnimationProperty = GetClass()->FindPropertyByName("ActiveAnimation");
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(ActiveAnimationProperty))
	{
		if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue(ObjectProperty->ContainerPtrToValuePtr<void>(this))))
		{
			ActiveAnimation = WidgetAnimation;
		}
	}

	FProperty* InactiveAnimationProperty = GetClass()->FindPropertyByName("InactiveAnimation");
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(InactiveAnimationProperty))
	{
		if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue(ObjectProperty->ContainerPtrToValuePtr<void>(this))))
		{
			InactiveAnimation = WidgetAnimation;
		}
	}

	/* 传递当前UI，计算Slate所需大小 */
	TakeWidget()->SlatePrepass();
}

bool UUserWidgetBase::HasActivationAnimation_Implementation(const bool InIsActive) const
{
	return InIsActive ? IsValid(ActiveAnimation) : IsValid(InactiveAnimation);
}

UWidgetAnimation* UUserWidgetBase::GetActiveAnimation_Implementation() const
{
	return ActiveAnimation;
}

void UUserWidgetBase::SetActiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetActiveAnimation_Implementation(InAnimation);
	ActiveAnimation = InAnimation;
}

UWidgetAnimation* UUserWidgetBase::GetInactiveAnimation_Implementation() const
{
	return InactiveAnimation;
}

void UUserWidgetBase::SetInactiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetInactiveAnimation_Implementation(InAnimation);
	InactiveAnimation = InAnimation;
}

void UUserWidgetBase::PlayActivationAnimation_Implementation(bool InIsActive)
{
	IWidgetAnimationInterface::PlayActivationAnimation_Implementation(InIsActive);

	if (InIsActive)
	{
		if (IsValid(Execute_GetActiveAnimation(this)))
		{
			PlayAnimation(Execute_GetActiveAnimation(this));
		}
	}
	else
	{
		if (IsValid(Execute_GetInactiveAnimation(this)))
		{
			PlayAnimation(Execute_GetInactiveAnimation(this));
		}
	}
}

float UUserWidgetBase::GetActivationAnimationDuration_Implementation(const bool InIsActive)
{
	IWidgetAnimationInterface::GetActivationAnimationDuration_Implementation(InIsActive);

	if (InIsActive)
	{
		if (IsValid(Execute_GetActiveAnimation(this)))
		{
			return Execute_GetActiveAnimation(this)->GetEndTime();
		}
	}
	else
	{
		if (IsValid(Execute_GetInactiveAnimation(this)))
		{
			return Execute_GetInactiveAnimation(this)->GetEndTime();
		}
	}

	return 0.f;
}

FVector2D UUserWidgetBase::GetAnchorOffset() const
{
	return FVector2D(-(GetDesiredSize().X * Anchor.X), -(GetDesiredSize().Y * Anchor.Y));
}
