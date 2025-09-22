// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Base/GenericWidget.h"

#include "WidgetType.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScaleBox.h"
#include "Components/ScaleBoxSlot.h"
#include "MVVM/WidgetDescriptionViewModel.h"
#include "MVVM/WidgetRenderViewModel.h"

UGenericWidget::UGenericWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bHasInitialized(false)
{
}

void UGenericWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	NativePreConstruct();
}

bool UGenericWidget::Initialize()
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

void UGenericWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UGenericWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ScaleBox.IsValid())
	{
		ScaleBox->SetUserSpecifiedScale(Scale);
	}
}

void UGenericWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FProperty* ActiveAnimationProperty = GetClass()->FindPropertyByName("ActiveAnimation");
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(ActiveAnimationProperty))
	{
		if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue(ObjectProperty->ContainerPtrToValuePtr<void>(this))))
		{
			SetActiveAnimation(WidgetAnimation);
		}
	}

	FProperty* InactiveAnimationProperty = GetClass()->FindPropertyByName("InactiveAnimation");
	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(InactiveAnimationProperty))
	{
		if (UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue(ObjectProperty->ContainerPtrToValuePtr<void>(this))))
		{
			SetInactiveAnimation(WidgetAnimation);
		}
	}

	/* 传递当前UI，计算Slate所需大小 */
	TakeWidget()->SlatePrepass(FSlateApplicationBase::Get().GetApplicationScale());
}

void UGenericWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (WidgetDescriptionViewModel)
	{
		WidgetDescriptionViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	if (WidgetRenderViewModel)
	{
		WidgetRenderViewModel->RemoveAllFieldValueChangedDelegates(this);
	}
}

/* ==================== UWidgetDescriptionViewModel ==================== */

UWidgetDescriptionViewModel* UGenericWidget::GetWidgetDescriptionViewModel() const
{
	return WidgetDescriptionViewModel;
}

void UGenericWidget::SetWidgetDescriptionViewModel(UWidgetDescriptionViewModel* InViewModel)
{
	if (WidgetDescriptionViewModel)
	{
		WidgetDescriptionViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	WidgetDescriptionViewModel = InViewModel;

	if (WidgetDescriptionViewModel)
	{
		REGISTER_MVVM_PROPERTY(WidgetDescriptionViewModel, PrimaryName, OnPrimaryNameChanged, true)
		REGISTER_MVVM_PROPERTY(WidgetDescriptionViewModel, SecondaryName, OnSecondaryNameChanged, true)
		REGISTER_MVVM_PROPERTY(WidgetDescriptionViewModel, TooltipText, OnTooltipTextChanged, true)
	}
}

void UGenericWidget::OnPrimaryNameChanged_Implementation(const FText& InPrimaryName)
{
}

void UGenericWidget::OnSecondaryNameChanged_Implementation(const FText& InSecondaryName)
{
}

void UGenericWidget::OnTooltipTextChanged_Implementation(const FText& InTooltipText)
{
	if (!InTooltipText.IsEmpty())
	{
		SetToolTipText(InTooltipText);
	}
}

/* ==================== UWidgetRenderViewModel ==================== */

UWidgetRenderViewModel* UGenericWidget::GetWidgetRenderViewModel() const
{
	return WidgetRenderViewModel;
}

void UGenericWidget::SetWidgetRenderViewModel(UWidgetRenderViewModel* InViewModel)
{
	if (WidgetRenderViewModel)
	{
		WidgetRenderViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	WidgetRenderViewModel = InViewModel;

	if (WidgetRenderViewModel)
	{
		REGISTER_MVVM_PROPERTY(WidgetRenderViewModel, Visibility, OnVisibilityChanged, true)
		REGISTER_MVVM_PROPERTY(WidgetRenderViewModel, RenderTransformPivot, OnRenderTransformPivotChanged, true)
		REGISTER_MVVM_PROPERTY(WidgetRenderViewModel, RenderTransform, OnRenderTransformChanged, true)
	}
}

void UGenericWidget::OnVisibilityChanged_Implementation(ESlateVisibility InVisibility)
{
	SetVisibility(InVisibility);
}

void UGenericWidget::OnRenderTransformPivotChanged_Implementation(FVector2D InRenderTransformPivot)
{
	SetRenderTransformPivot(InRenderTransformPivot);
}

void UGenericWidget::OnRenderTransformChanged_Implementation(const FWidgetTransform& InRenderTransform)
{
	SetRenderTransform(InRenderTransform);
}

/* ==================== IStateInterface ==================== */

void UGenericWidget::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	WidgetTree->ForEachWidget([&](UWidget* Widget)
		{
			if (IStateInterface* StateInterface = Cast<IStateInterface>(Widget))
			{
				StateInterface->NativeOnCreate();
			}
		}
	);
}

void UGenericWidget::NativeOnActived()
{
	IStateInterface::NativeOnActived();

	WidgetTree->ForEachWidget([](UWidget* Widget)
		{
			if (IStateInterface* StateInterface = Cast<IStateInterface>(Widget))
			{
				StateInterface->NativeOnActived();
			}
		}
	);
}

void UGenericWidget::NativeOnActivedFinish()
{
	IStateInterface::NativeOnActivedFinish();
}

void UGenericWidget::NativeOnInactived()
{
	IStateInterface::NativeOnInactived();

	WidgetTree->ForEachWidget([](UWidget* Widget)
		{
			if (IStateInterface* StateInterface = Cast<IStateInterface>(Widget))
			{
				StateInterface->NativeOnInactived();
			}
		}
	);
}

void UGenericWidget::NativeOnInactivedFinish()
{
	IStateInterface::NativeOnInactivedFinish();
}

void UGenericWidget::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
}

bool UGenericWidget::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UGenericWidget::SetIsActived(const bool InActived)
{
	// IStateInterface::SetIsActived(InActived);

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

void UGenericWidget::OnActiveStateChanged()
{
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

		/* Play Widget Animation */
		PlayWidgetAnimation(GetIsActived());
	}
}

/* ==================== IWidgetChildrenInterface ==================== */

UGenericWidget* UGenericWidget::GetChildByIndex(int32 InIndex)
{
	if (!Children.IsValidIndex(InIndex))
	{
		return Children[InIndex].Get();
	}
	return nullptr;
}

void UGenericWidget::AddChild(UGenericWidget* InWidget)
{
	if (IsValid(InWidget) && !Children.Contains(InWidget))
	{
		Children.Add(InWidget);
		OnChildAdded(InWidget, Children.Find(InWidget));
	}
}

void UGenericWidget::RemoveChild(int32 InIndex)
{
	if (Children.IsValidIndex(InIndex))
	{
		RemoveChild(Children[InIndex].Get());
	}
}

void UGenericWidget::RemoveChild(UGenericWidget* InWidget)
{
	if (IsValid(InWidget) && Children.Contains(InWidget))
	{
		OnChildRemoved(InWidget, Children.Find(InWidget));
		Children.Remove(InWidget);
	}
}

void UGenericWidget::ClearChildren()
{
	Children.Reset();
}

void UGenericWidget::OnChildAdded_Implementation(UGenericWidget* InWidget, int32 InIndex)
{
}

void UGenericWidget::OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 InIndex)
{
}

/* ==================== IWidgetAnimationInterface ==================== */

bool UGenericWidget::HasWidgetAnimation(const bool InIsActive) const
{
	return InIsActive ? IsValid(ActivedAnimation) : IsValid(InactivedAnimation);
}

bool UGenericWidget::IsPlayingWidgetAnimation(bool InIsActive) const
{
	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		return IsAnimationPlaying(Animation);
	}

	return false;
}

float UGenericWidget::GetWidgetAnimationDuration(const bool InIsActive)
{
	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		return Animation->GetEndTime();
	}

	return 0.f;
}

UWidgetAnimation* UGenericWidget::GetActiveAnimation() const
{
	return ActivedAnimation;
}

void UGenericWidget::SetActiveAnimation(UWidgetAnimation* InAnimation)
{
	if (IsValid(ActivedAnimation))
	{
		UnbindFromAnimationFinished(ActivedAnimation, WidgetActiveAnimationFinishBinding);
	}

	ActivedAnimation = InAnimation;
	WidgetActiveAnimationFinishBinding.BindDynamic(this, &UGenericWidget::OnWidgetActiveAnimationPlayFinish);

	BindToAnimationFinished(ActivedAnimation, WidgetActiveAnimationFinishBinding);
}

UWidgetAnimation* UGenericWidget::GetInactiveAnimation() const
{
	return InactivedAnimation;
}

void UGenericWidget::SetInactiveAnimation(UWidgetAnimation* InAnimation)
{
	if (IsValid(InactivedAnimation))
	{
		UnbindFromAnimationFinished(InactivedAnimation, WidgetInactiveAnimationFinishBinding);
	}

	InactivedAnimation = InAnimation;
	WidgetInactiveAnimationFinishBinding.BindDynamic(this, &UGenericWidget::OnWidgetInactiveAnimationPlayFinish);

	BindToAnimationFinished(InactivedAnimation, WidgetInactiveAnimationFinishBinding);
}

void UGenericWidget::PlayWidgetAnimation(bool InIsActive)
{
	/**	Check Has Widget Animation */
	if (!HasWidgetAnimation(GetIsActived()))
	{
		if (GetIsActived())
		{
			OnWidgetActiveAnimationPlayFinish();
		}
		else
		{
			OnWidgetInactiveAnimationPlayFinish();
		}
		return;
	}

	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(InIsActive ? GetActiveAnimation() : GetInactiveAnimation());
}

void UGenericWidget::PlayWidgetAnimationRollback(bool InIsActive)
{
	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		ReverseAnimation(Animation);
	}
}

void UGenericWidget::PauseWidgetAnimation(bool InIsActive)
{
	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		PauseAnimation(Animation);
	}
}

void UGenericWidget::StopWidgetAnimation(bool InIsActive)
{
	if (const UWidgetAnimation* Animation = InIsActive ? GetActiveAnimation() : GetInactiveAnimation())
	{
		StopAnimation(Animation);
	}
}

void UGenericWidget::OnWidgetActiveAnimationPlayFinish()
{
	NativeOnActivedFinish();
	OnWidgetActiveAnimationPlayFinishEvent.Broadcast(this);
}

void UGenericWidget::OnWidgetInactiveAnimationPlayFinish()
{
	SetVisibility(ESlateVisibility::Collapsed);
	NativeOnInactivedFinish();
	OnWidgetInactiveAnimationPlayFinishEvent.Broadcast(this);
}
