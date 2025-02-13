// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/UserWidgetBase.h"

#include "CommonInputSubsystem.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScaleBox.h"
#include "Components/ScaleBoxSlot.h"
#include "Entity/WidgetEntity.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Input/CommonUIInputTypes.h"

UUserWidgetBase::UUserWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UUserWidgetBase::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		UScaleBox* NewScaleBox = WidgetTree->ConstructWidget<UScaleBox>(UScaleBox::StaticClass(), FName(TEXT("ScaleBox")));
		NewScaleBox->SetStretch(EStretch::UserSpecified);
		NewScaleBox->SetStretchDirection(EStretchDirection::Both);
		ScaleBox = NewScaleBox;

		if (WidgetTree->RootWidget)
		{
			UScaleBoxSlot* NewSlot = Cast<UScaleBoxSlot>(ScaleBox->AddChild(WidgetTree->RootWidget));
			NewSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			NewSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}

		WidgetTree->RootWidget = NewScaleBox;
	}

	/* 传递当前UI，计算Slate所需大小 */
	TakeWidget()->SlatePrepass();

	return bInitializedThisCall;
}

void UUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ScaleBox.IsValid())
	{
		ScaleBox->SetUserSpecifiedScale(Scale);
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
			ActivedAnimation = WidgetAnimation;
		}
	}

	FProperty* InactiveAnimationProperty = GetClass()->FindPropertyByName("InactiveAnimation");
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(InactiveAnimationProperty))
	{
		if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue(ObjectProperty->ContainerPtrToValuePtr<void>(this))))
		{
			InactivedAnimation = WidgetAnimation;
		}
	}

	/* 传递当前UI，计算Slate所需大小 */
	TakeWidget()->SlatePrepass();
}

void UUserWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
}

FVector2D UUserWidgetBase::GetAnchorOffset() const
{
	return FVector2D(-(GetDesiredSize().X * Anchor.X), -(GetDesiredSize().Y * Anchor.Y));
}

/* ==================== WidgetEntity ==================== */

UWidgetEntity* UUserWidgetBase::GetWidgetEntity()
{
	return GetWidgetEntity<UWidgetEntity>();
}

UWidgetEntity* UUserWidgetBase::GetWidgetEntityByClass(TSubclassOf<UWidgetEntity> InClass)
{
	ensure(InClass);
	return GetWidgetEntity<UWidgetEntity>();
}

void UUserWidgetBase::SetWidgetEntity(UWidgetEntity* InWidgetEntity)
{
	if (!IsValid(InWidgetEntity))
	{
		DLOG(DLogUI, Error, TEXT("InWidgetEntity Is InValid"))
	}

	WidgetEntity = InWidgetEntity;
}

/* ==================== IStateInterface ==================== */

bool UUserWidgetBase::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UUserWidgetBase::SetIsActived(const bool InActived)
{
	IStateInterface::SetIsActived(InActived);

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
	return InIsActive ? IsValid(ActivedAnimation) : IsValid(InactivedAnimation);
}

bool UUserWidgetBase::IsPlayingWidgetAnimation(bool InIsActive) const
{
	const bool Result = IWidgetAnimationInterface::IsPlayingWidgetAnimation(InIsActive);

	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		return IsAnimationPlaying(Animation);
	}

	return Result;
}

UWidgetAnimation* UUserWidgetBase::GetActiveAnimation() const
{
	return ActivedAnimation;
}

void UUserWidgetBase::SetActiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetActiveAnimation_Implementation(InAnimation);
	ActivedAnimation = InAnimation;
}

UWidgetAnimation* UUserWidgetBase::GetInactiveAnimation() const
{
	return InactivedAnimation;
}

void UUserWidgetBase::SetInactiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetInactiveAnimation_Implementation(InAnimation);
	InactivedAnimation = InAnimation;
}

void UUserWidgetBase::PlayWidgetAnimation(bool InIsActive)
{
	IWidgetAnimationInterface::PlayWidgetAnimation(InIsActive);

	if (UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		PlayAnimation(Animation);
	}
}

void UUserWidgetBase::PlayWidgetAnimationRollback(bool InIsActive)
{
	IWidgetAnimationInterface::PlayWidgetAnimationRollback(InIsActive);

	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		ReverseAnimation(Animation);
	}
}

void UUserWidgetBase::PauseWidgetAnimation(bool InIsActive)
{
	IWidgetAnimationInterface::PauseWidgetAnimation(InIsActive);

	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		PauseAnimation(Animation);
	}
}

void UUserWidgetBase::StopWidgetAnimation(bool InIsActive)
{
	IWidgetAnimationInterface::StopWidgetAnimation(InIsActive);

	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		StopAnimation(Animation);
	}
}

float UUserWidgetBase::GetWidgetAnimationDuration(const bool InIsActive)
{
	const float Result = IWidgetAnimationInterface::GetWidgetAnimationDuration(InIsActive);

	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		return Animation->GetEndTime();
	}

	return Result;
}
