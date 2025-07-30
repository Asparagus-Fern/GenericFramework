// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericGameSlotManager.h"

#include "GenericGameHUDManager.h"

#include "GenericWidgetManager.h"
#include "Base/GenericGameHUD.h"
#include "Base/GenericWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Manager/ManagerStatics.h"
#include "UWidget/GameplayTagSlot.h"

bool UGenericGameSlotManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
}

void UGenericGameSlotManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGameplayTagSlot::OnBuildGameplayTagSlot.AddUObject(this, &UGenericGameSlotManager::RegisterSlot);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.AddUObject(this, &UGenericGameSlotManager::UnRegisterSlot);

	UGenericWidgetManager::Delegate_PreWidgetOpened.AddUObject(this, &UGenericGameSlotManager::PreWidgetOpened);
	UGenericWidgetManager::Delegate_OnWidgetOpened.AddUObject(this, &UGenericGameSlotManager::OnWidgetOpened);

	UGenericWidgetManager::Delegate_PreWidgetClosed.AddUObject(this, &UGenericGameSlotManager::PreWidgetClosed);
	UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(this, &UGenericGameSlotManager::PostWidgetClosed);

	RegisterManager(this);
}

void UGenericGameSlotManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UGameplayTagSlot::OnBuildGameplayTagSlot.RemoveAll(this);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.RemoveAll(this);

	UGenericWidgetManager::Delegate_PreWidgetOpened.RemoveAll(this);
	UGenericWidgetManager::Delegate_OnWidgetOpened.RemoveAll(this);

	UGenericWidgetManager::Delegate_PreWidgetClosed.RemoveAll(this);
	UGenericWidgetManager::Delegate_PostWidgetClosed.RemoveAll(this);
}

bool UGenericGameSlotManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGenericGameSlotManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FManagerInterface::HandleOnWorldMatchStarting(InWorld);
}

void UGenericGameSlotManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FManagerInterface::HandleOnWorldEndPlay(InWorld);
	Slots.Reset();
}

/* ==================== DelegateBinding ==================== */

void UGenericGameSlotManager::PreWidgetOpened(FOpenWidgetParameter& Parameter)
{
	Parameter.Slot = GetSlot(Parameter.SlotTag);
	Parameter.WidgetToRemove = GetSlotWidget(Parameter.SlotTag);
}

void UGenericGameSlotManager::OnWidgetOpened(FOpenWidgetParameter& Parameter)
{
	bool Result = AddSlotWidget(Parameter.WidgetToHandle);
	Parameter.bOpenResult = Result;
}

void UGenericGameSlotManager::PreWidgetClosed(FCloseWidgetParameter& Parameter)
{
	Parameter.Slot = GetSlot(Parameter.SlotTag);

	if (!Parameter.WidgetToHandle)
	{
		Parameter.WidgetToHandle = GetSlotWidget(Parameter.SlotTag);
	}
}

void UGenericGameSlotManager::PostWidgetClosed(UGenericWidget* InWidget)
{
	InWidget->RemoveFromParent();
}

/* ==================== UGameplayTagSlot ==================== */

void UGenericGameSlotManager::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot))
	{
		GenericLOG(GenericLogUI, Error, TEXT("GameplayTagSlot Is InValid"))
		return;
	}

	if (!InSlot->SlotTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("SlotTag Is InValid"))
		return;
	}

	if (Slots.Contains(InSlot))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("GameplayTag : %s Is Already Register"), *InSlot->SlotTag.ToString())
		return;
	}

	InSlot->ClearChildren();
	Slots.Add(InSlot);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnSlotRegister, BPDelegate_OnSlotRegister, InSlot)
}

void UGenericGameSlotManager::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (!IsValid(InSlot))
	{
		GenericLOG(GenericLogUI, Error, TEXT("GameplayTagSlot Is InValid"))
		return;
	}

	if (!InSlot->SlotTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("SlotTag Is InValid"))
		return;
	}

	if (!Slots.Contains(InSlot))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("GameplayTag : %s Is Already UnRegister"), *InSlot->SlotTag.ToString())
		return;
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnSlotUnRegister, BPDelegate_OnSlotUnRegister, InSlot)
	Slots.Remove(InSlot);
}

UGameplayTagSlot* UGenericGameSlotManager::GetSlot(const UGenericWidget* InWidget) const
{
	if (!IsValid(InWidget))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWidget Is InValid"))
		return nullptr;
	}

	return GetSlot(InWidget->SlotTag);
}

UGameplayTagSlot* UGenericGameSlotManager::GetSlot(const FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		// GenericLOG(GenericLogUI, Warning, TEXT("SlotTag Is InValid"))
		return nullptr;
	}

	for (const auto& Slot : Slots)
	{
		if (Slot->SlotTag == InSlotTag)
		{
			return Slot;
		}
	}

	return nullptr;
}

UGenericWidget* UGenericGameSlotManager::GetSlotWidget(FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		// GenericLOG(GenericLogUI, Error, TEXT("SlotTag Is InValid"))
		return nullptr;
	}

	for (const auto& Slot : Slots)
	{
		if (!Slot->HasAnyChildren())
		{
			continue;
		}

		if (Slot->SlotTag == InSlotTag)
		{
			return Cast<UGenericWidget>(Slot->GetChildAt(0));
		}
	}

	return nullptr;
}

TArray<UGenericWidget*> UGenericGameSlotManager::GetSlotWidgets() const
{
	TArray<UGenericWidget*> Result;

	for (const auto& Slot : Slots)
	{
		if (!Slot->HasAnyChildren())
		{
			continue;
		}

		if (UGenericWidget* Widget = Cast<UGenericWidget>(Slot->GetChildAt(0)))
		{
			Result.Add(Widget);
		}
	}

	return Result;
}

bool UGenericGameSlotManager::AddSlotWidget(UGenericWidget* InWidget) const
{
	if (InWidget->SlotTag.IsValid())
	{
		if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
		{
			Slot->AddChild(InWidget);
			return true;
		}
		else
		{
			GenericLOG(GenericLogUI, Warning, TEXT("Slot Is InValid"))
		}
	}
	else
	{
		if (UGenericGameHUD* GameHUD = Cast<UGenericGameHUD>(InWidget))
		{
			InWidget->AddToViewport(GameHUD->ViewportZOrder);
			return true;
		}
		else if (UWidgetTree* WidgetTree = Cast<UWidgetTree>(InWidget->GetOuter()))
		{
			if (UGenericWidget* Widget = Cast<UGenericWidget>(WidgetTree->GetOuter()))
			{
				Widget->AddChild(InWidget);
				return true;
			}
		}
	}

	return false;
}

bool UGenericGameSlotManager::RemoveSlotWidget(UGenericWidget* InWidget) const
{
	if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
	{
		return Slot->RemoveChild(InWidget);
	}

	return false;
}
