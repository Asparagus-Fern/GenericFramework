// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WidgetAnimationManager.h"

#include "WidgetManager.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Base/UserWidgetBase.h"

/* ==================== FWidgetAnimationTimerHandle ==================== */

FWidgetAnimationTimerHandle::FWidgetAnimationTimerHandle()
{
}

FWidgetAnimationTimerHandle::FWidgetAnimationTimerHandle(UUserWidgetBase* InWidget, bool InIsActive, FTimerHandle InTimerHandle)
	: Widget(InWidget),
	  bIsActive(InIsActive),
	  TimerHandle(InTimerHandle)
{
}

bool FWidgetAnimationTimerHandle::operator==(const FWidgetAnimationTimerHandle& Other) const
{
	return Widget == Other.Widget;
}

bool FWidgetAnimationTimerHandle::operator==(const UUserWidgetBase* Other) const
{
	return Widget == Other;
}

/* ==================== UWidgetAnimationManager ==================== */

bool UWidgetAnimationManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWidgetAnimationManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UWidgetManager::Delegate_OnWidgetOpened.AddUObject(this, &UWidgetAnimationManager::OnWidgetOpened);
	UWidgetManager::Delegate_OnWidgetClosed.AddUObject(this, &UWidgetAnimationManager::OnWidgetClosed);
}

void UWidgetAnimationManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UWidgetManager::Delegate_OnWidgetOpened.RemoveAll(this);
	UWidgetManager::Delegate_OnWidgetClosed.RemoveAll(this);
}

bool UWidgetAnimationManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWidgetAnimationManager::OnWidgetOpened(UUserWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return;
	}

	/* Play Widget Actived Animation After Open Widget */
	if (PlayWidgetAnimation(InWidget, true, FTimerDelegate::CreateUObject(this, &UWidgetAnimationManager::OnActiveAnimationPlayFinish, InWidget)))
	{
		return;
	}
	else
	{
		OnActiveAnimationPlayFinish(InWidget);
	}
}

void UWidgetAnimationManager::OnWidgetClosed(UUserWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return;
	}

	/* Play Widget Inactived Animation Before Close Widget */
	if (PlayWidgetAnimation(InWidget, false, FTimerDelegate::CreateUObject(this, &UWidgetAnimationManager::OnInactiveAnimationPlayFinish, InWidget)))
	{
		return;
	}
	else
	{
		OnInactiveAnimationPlayFinish(InWidget);
	}
}

bool UWidgetAnimationManager::PlayWidgetAnimation(UUserWidgetBase* InWidget, bool InIsActive, const FTimerDelegate& InDelegate)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return false;
	}

	/* Play Only Has Animation And Animation EndTime > 0 */
	if (InWidget->HasWidgetAnimation(InIsActive) && InWidget->GetWidgetAnimationDuration(InIsActive) > 0.f)
	{
		/* Animation Is Already Playing */
		if (InWidget->IsPlayingWidgetAnimation(InIsActive))
		{
			DLOG(DLogUI, Warning, TEXT("WidgetAnimation Is Playing"))
			return true;
		}

		/* Clear Timer That Last Playing Animation Has Not Finish */
		if (InWidget->IsPlayingWidgetAnimation(!InIsActive))
		{
			InWidget->StopWidgetAnimation(!InIsActive);

			if (FWidgetAnimationTimerHandle* Found = WidgetAnimationTimerHandles.FindByKey(InWidget))
			{
				GetWorld()->GetTimerManager().ClearTimer(Found->TimerHandle);
				WidgetAnimationTimerHandles.Remove(*Found);
			}
		}

		/* Set Timer And Play */
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, InDelegate, InWidget->GetWidgetAnimationDuration(InIsActive), false);
		WidgetAnimationTimerHandles.Add(FWidgetAnimationTimerHandle(InWidget, InIsActive, TimerHandle));

		InWidget->PlayWidgetAnimation(InIsActive);
		return true;
	}

	return false;
}

void UWidgetAnimationManager::OnActiveAnimationPlayFinish(UUserWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return;
	}

	/* Clear And Broadcast */
	if (FWidgetAnimationTimerHandle* Found = WidgetAnimationTimerHandles.FindByKey(InWidget))
	{
		GetWorld()->GetTimerManager().ClearTimer(Found->TimerHandle);
		WidgetAnimationTimerHandles.Remove(*Found);
	}

	InWidget->NativeOnActivedFinish();
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetAnimationPlayFinish, BPDelegate_OnWidgetAnimationPlayFinish, InWidget, true);
}

void UWidgetAnimationManager::OnInactiveAnimationPlayFinish(UUserWidgetBase* InWidget)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return;
	}

	/* Clear And Broadcast */
	if (FWidgetAnimationTimerHandle* Found = WidgetAnimationTimerHandles.FindByKey(InWidget))
	{
		GetWorld()->GetTimerManager().ClearTimer(Found->TimerHandle);
		WidgetAnimationTimerHandles.Remove(*Found);
	}

	InWidget->NativeOnInactivedFinish();
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetAnimationPlayFinish, BPDelegate_OnWidgetAnimationPlayFinish, InWidget, false);
}
