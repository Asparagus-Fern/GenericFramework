// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Base/UserWidgetBase.h"

#include "WidgetEntityManager.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScaleBox.h"
#include "Components/ScaleBoxSlot.h"
#include "Entity/WidgetEntity.h"
#include "Manager/ManagerStatics.h"

UUserWidgetBase::UUserWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bHasInitialized(false)
{
}

void UUserWidgetBase::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	NativePreConstruct();
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

	return bInitializedThisCall;
}

void UUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
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
			Execute_SetActiveAnimation(this, WidgetAnimation);
		}
	}

	FProperty* InactiveAnimationProperty = GetClass()->FindPropertyByName("InactiveAnimation");
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(InactiveAnimationProperty))
	{
		if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue(ObjectProperty->ContainerPtrToValuePtr<void>(this))))
		{
			Execute_SetInactiveAnimation(this, WidgetAnimation);
		}
	}

	/* 传递当前UI，计算Slate所需大小 */
	TakeWidget()->SlatePrepass();

	if (IsValid(WidgetEntity))
	{
		if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
		{
			WidgetEntity->SetWidget(this);
			WidgetEntityManager->RegisterWidgetEntity(WidgetEntity);
		}
	}
}

void UUserWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
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
		return;
	}

	if (WidgetEntity == InWidgetEntity)
	{
		return;
	}

	if (IsValid(WidgetEntity))
	{
		WidgetEntity->NativeOnDestroy();
	}

	WidgetEntity = InWidgetEntity;
	WidgetEntity->NativeOnCreate();
}

/* ==================== IStateInterface ==================== */

bool UUserWidgetBase::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UUserWidgetBase::SetIsActived(const bool InActived)
{
	if (InActived != GetIsActived())
	{
		bIsActived = InActived;

		if (!bHasInitialized)
		{
			Initialize();
			bHasInitialized = true;
		}

		OnActiveStateChanged();
	}
}

void UUserWidgetBase::OnActiveStateChanged()
{
	IStateInterface::OnActiveStateChanged();

	if (const UWorld* World = GetWorld())
	{
		/* Check Is Game World */
		if (!World->IsGameWorld())
		{
			if (GetIsActived())
			{
				SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				SetVisibility(ESlateVisibility::Collapsed);
			}
			return;
		}

		/*	Check Has Widget Animation */
		if (!HasWidgetAnimation(GetIsActived()))
		{
			if (GetIsActived())
			{
				OnWidgetActiveAnimationFinish();
			}
			else
			{
				OnWidgetInactiveAnimationFinish();
			}
			return;
		}

		/* Play Widget Animation */
		if (GetIsActived())
		{
			SetVisibility(ESlateVisibility::Visible);
		}

		PlayWidgetAnimation(GetIsActived());
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

	if (IsValid(ActivedAnimation))
	{
		UnbindFromAnimationFinished(ActivedAnimation, WidgetActiveAnimationFinishBinding);
	}

	ActivedAnimation = InAnimation;
	WidgetActiveAnimationFinishBinding.BindDynamic(this, &UUserWidgetBase::OnWidgetActiveAnimationFinish);

	BindToAnimationFinished(ActivedAnimation, WidgetActiveAnimationFinishBinding);
}

UWidgetAnimation* UUserWidgetBase::GetInactiveAnimation() const
{
	return InactivedAnimation;
}

void UUserWidgetBase::SetInactiveAnimation_Implementation(UWidgetAnimation* InAnimation)
{
	IWidgetAnimationInterface::SetInactiveAnimation_Implementation(InAnimation);

	if (IsValid(InactivedAnimation))
	{
		UnbindFromAnimationFinished(InactivedAnimation, WidgetInactiveAnimationFinishBinding);
	}

	InactivedAnimation = InAnimation;
	WidgetInactiveAnimationFinishBinding.BindDynamic(this, &UUserWidgetBase::OnWidgetInactiveAnimationFinish);

	BindToAnimationFinished(InactivedAnimation, WidgetInactiveAnimationFinishBinding);
}

void UUserWidgetBase::OnWidgetActiveAnimationFinish()
{
}

void UUserWidgetBase::OnWidgetInactiveAnimationFinish()
{
	SetVisibility(ESlateVisibility::Collapsed);
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
