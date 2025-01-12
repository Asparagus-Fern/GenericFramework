// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/UserWidgetBase.h"

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

void UUserWidgetBase::SetActiveState_Implementation(bool InActiveState)
{
	IProcedureInterface::SetActiveState_Implementation(InActiveState);
	SetIsActived(InActiveState);
}

void UUserWidgetBase::SetIsActived(const bool InActived)
{
	IProcedureInterface::SetIsActived(InActived);

	if (HasWidgetAnimation(InActived))
	{
		PlayWidgetAnimation(InActived);
	}
	else
	{
		SetVisibility(InActived ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

/* ==================== IWidgetAnimationInterface ==================== */

bool UUserWidgetBase::HasWidgetAnimation(const bool InIsActive) const
{
	return InIsActive ? IsValid(ActiveAnimation) : IsValid(InactiveAnimation);
}

UWidgetAnimation* UUserWidgetBase::GetActiveAnimation() const
{
	return ActiveAnimation;
}

void UUserWidgetBase::SetActiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetActiveAnimation_Implementation(InAnimation);
	ActiveAnimation = InAnimation;
}

UWidgetAnimation* UUserWidgetBase::GetInactiveAnimation() const
{
	return InactiveAnimation;
}

void UUserWidgetBase::SetInactiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetInactiveAnimation_Implementation(InAnimation);
	InactiveAnimation = InAnimation;
}

void UUserWidgetBase::PlayWidgetAnimation(bool InIsActive)
{
	IWidgetAnimationInterface::PlayWidgetAnimation(InIsActive);

	if (UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		PlayAnimation(Animation);
	}
}

float UUserWidgetBase::GetWidgetAnimationDuration(const bool InIsActive)
{
	IWidgetAnimationInterface::GetWidgetAnimationDuration(InIsActive);

	if (UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		return Animation->GetEndTime();
	}

	return 0.f;
}

FVector2D UUserWidgetBase::GetAnchorOffset() const
{
	return FVector2D(-(GetDesiredSize().X * Anchor.X), -(GetDesiredSize().Y * Anchor.Y));
}
