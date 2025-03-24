// Copyright ChenTaiye 2025. All Rights Reserved.


#include "WidgetManager.h"

#include "WidgetAnimationManager.h"
#include "Base/UserWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "UWidget/Override/GameplayTagSlot.h"

/* ==================== FReplaceWidgetHandle ==================== */

FReplaceWidgetHandle::FReplaceWidgetHandle()
{
}

FReplaceWidgetHandle::FReplaceWidgetHandle(FGameplayTag InSlotTag, UUserWidgetBase* InNewWidget, const FOnWidgetActiveStateChanged& OnFinish)
	: SlotTag(InSlotTag),
	  NewWidget(InNewWidget),
	  OnFinishDelegate(OnFinish)
{
}

/* ==================== UWidgetManager ==================== */

bool UWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.AddUObject(this, &UWidgetManager::OnWidgetAnimationPlayFinish);
}

void UWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.RemoveAll(this);
}

bool UWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UWidgetManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);
}

void UWidgetManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	if (RequestRemoveGameplayTagSlotWidget.IsBound())
	{
		for (auto& ActivedWidget : ActivedWidgets)
		{
			ActivedWidget->NativeOnInactived();
			RequestRemoveGameplayTagSlotWidget.Execute(ActivedWidget);
			ActivedWidget->NativeOnInactivedFinish();
		}
	}

	for (const auto& ActivedWidget : ActivedWidgets)
	{
		ActivedWidget->SetGarbageAtDestroy(true);
		ActivedWidget->NativeOnDestroy();
	}

	ActivedWidgets.Reset();
	ReplaceWidgetHandles.Reset();
}

void UWidgetManager::OnWidgetAnimationPlayFinish(UUserWidgetBase* InWidget, bool InIsActive)
{
	if (InIsActive)
	{
		FWidgetDelegate::OnWidgetActualOpened.Broadcast(InWidget);

		if (const FReplaceWidgetHandle* Found = ReplaceWidgetHandles.FindByKey(InWidget->SlotTag))
		{
			ReplaceWidgetHandles.Remove(*Found);
		}
	}
	else
	{
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetClosed, BPDelegate_PostWidgetClosed, InWidget);

		InWidget->NativeOnDestroy();
		InWidget->RemoveFromParent();

		FWidgetDelegate::OnWidgetActualClosed.Broadcast(InWidget);
		ActivedWidgets.Remove(InWidget);

		/* Need To Replace Widget In This Slot */
		if (const FReplaceWidgetHandle* Found = ReplaceWidgetHandles.FindByKey(InWidget->SlotTag))
		{
			ActiveWidget(Found->NewWidget, Found->OnFinishDelegate);
		}
	}
}

UUserWidgetBase* UWidgetManager::OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FOnWidgetActiveStateChanged OnFinish)
{
	UUserWidgetBase* NewWidget = CreateWidget<UUserWidgetBase>(GetWorld(), InWidgetClass);
	if (OpenUserWidget(NewWidget, OnFinish))
	{
		return NewWidget;
	}
	else
	{
		return nullptr;
	}
}

bool UWidgetManager::OpenUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		return false;
	}

	if (!InWidget->SlotTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("SlotTag Is InValid"))
		return false;
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_PreWidgetOpened, BPDelegate_PreWidgetOpened, InWidget);

	const UGameplayTagSlot* Slot = nullptr;
	if (RequestGameplayTagSlot.IsBound())
	{
		Slot = RequestGameplayTagSlot.Execute(InWidget);
	}

	if (IsValid(Slot))
	{
		InWidget->NativeOnCreate();

		UUserWidgetBase* RemoveWidget = nullptr;
		if (RequestGameplayTagSlotWidget.IsBound())
		{
			RemoveWidget = RequestGameplayTagSlotWidget.Execute(InWidget->SlotTag);
		}

		if (IsValid(RemoveWidget))
		{
			ReplaceWidgetHandles.Add(FReplaceWidgetHandle(InWidget->SlotTag, InWidget, OnFinish));
			InactiveWidget(RemoveWidget);
		}
		else
		{
			ActiveWidget(InWidget, OnFinish);
		}

		return true;
	}

	DLOG(DLogUI, Error, TEXT("GameplayTagSlot Is InValid"))
	return false;
}

bool UWidgetManager::CloseUserWidget(FGameplayTag InSlotTag, bool MarkAsGarbage, FOnWidgetActiveStateChanged OnFinish)
{
	if (!InSlotTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("SlotTag Is InValid"))
		return false;
	}

	if (RequestGameplayTagSlotWidget.IsBound())
	{
		if (UUserWidgetBase* Widget = RequestGameplayTagSlotWidget.Execute(InSlotTag))
		{
			return CloseUserWidget(Widget, MarkAsGarbage, OnFinish);
		}
	}

	DLOG(DLogUI, Error, TEXT("GameplayTagSlot Is InValid"))
	OnFinish.ExecuteIfBound(nullptr);
	return false;
}

bool UWidgetManager::CloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		OnFinish.ExecuteIfBound(InWidget);
		return false;
	}

	InactiveWidget(InWidget, MarkAsGarbage, OnFinish);
	return true;
}

void UWidgetManager::ActiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	if (ActivedWidgets.Contains(InWidget))
	{
		DLOG(DLogUI, Warning, TEXT("InWidget Is Already Actived"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	if (RequestAddGameplayTagSlotWidget.IsBound())
	{
		if (RequestAddGameplayTagSlotWidget.Execute(InWidget))
		{
			ActivedWidgets.Add(InWidget);
			InWidget->NativeOnActived();

			BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetOpened, BPDelegate_OnWidgetOpened, InWidget);
			OnFinish.ExecuteIfBound(InWidget);
		}
	}
}

void UWidgetManager::InactiveWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		DLOG(DLogUI, Error, TEXT("InWidget Is InValid"))
		OnFinish.ExecuteIfBound(InWidget);
		return;
	}

	InWidget->SetGarbageAtDestroy(MarkAsGarbage);
	InWidget->NativeOnInactived();
	OnFinish.ExecuteIfBound(InWidget);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetClosed, BPDelegate_OnWidgetClosed, InWidget);
}
