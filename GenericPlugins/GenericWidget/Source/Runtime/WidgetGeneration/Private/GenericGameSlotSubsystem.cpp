// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericGameSlotSubsystem.h"

#include "GenericWidgetSubsystem.h"
#include "Base/GenericGameHUD.h"
#include "Base/GenericWidget.h"
#include "Blueprint/WidgetTree.h"

#include "Type/GenericType.h"
#include "UWidget/GameplayTagSlot.h"

UGenericGameSlotSubsystem* UGenericGameSlotSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UGenericGameSlotSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGameplayTagSlot::OnBuildGameplayTagSlot.AddUObject(this, &UGenericGameSlotSubsystem::RegisterSlot);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.AddUObject(this, &UGenericGameSlotSubsystem::UnRegisterSlot);

	UGenericWidgetSubsystem::Delegate_PreWidgetOpened.AddUObject(this, &UGenericGameSlotSubsystem::PreWidgetOpened);
	UGenericWidgetSubsystem::Delegate_OnWidgetOpened.AddUObject(this, &UGenericGameSlotSubsystem::OnWidgetOpened);

	UGenericWidgetSubsystem::Delegate_PreWidgetClosed.AddUObject(this, &UGenericGameSlotSubsystem::PreWidgetClosed);
	UGenericWidgetSubsystem::Delegate_PostWidgetClosed.AddUObject(this, &UGenericGameSlotSubsystem::PostWidgetClosed);
}

void UGenericGameSlotSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UGameplayTagSlot::OnBuildGameplayTagSlot.RemoveAll(this);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.RemoveAll(this);

	UGenericWidgetSubsystem::Delegate_PreWidgetOpened.RemoveAll(this);
	UGenericWidgetSubsystem::Delegate_OnWidgetOpened.RemoveAll(this);

	UGenericWidgetSubsystem::Delegate_PreWidgetClosed.RemoveAll(this);
	UGenericWidgetSubsystem::Delegate_PostWidgetClosed.RemoveAll(this);

	Slots.Reset();
}

/* ==================== DelegateBinding ==================== */

void UGenericGameSlotSubsystem::PreWidgetOpened(FOpenWidgetParameter& Parameter)
{
	Parameter.Slot = GetSlot(Parameter.SlotTag);
	Parameter.WidgetToRemove = GetSlotWidget(Parameter.SlotTag);
}

void UGenericGameSlotSubsystem::OnWidgetOpened(FOpenWidgetParameter& Parameter)
{
	bool Result = AddSlotWidget(Parameter.WidgetToHandle);
	Parameter.bOpenResult = Result;
}

void UGenericGameSlotSubsystem::PreWidgetClosed(FCloseWidgetParameter& Parameter)
{
	Parameter.Slot = GetSlot(Parameter.SlotTag);

	if (!Parameter.WidgetToHandle)
	{
		Parameter.WidgetToHandle = GetSlotWidget(Parameter.SlotTag);
	}
}

void UGenericGameSlotSubsystem::PostWidgetClosed(UGenericWidget* InWidget)
{
	RemoveSlotWidget(InWidget);
}

/* ==================== UGameplayTagSlot ==================== */

void UGenericGameSlotSubsystem::RegisterSlot(UGameplayTagSlot* InSlot)
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

void UGenericGameSlotSubsystem::UnRegisterSlot(UGameplayTagSlot* InSlot)
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

UGameplayTagSlot* UGenericGameSlotSubsystem::GetSlot(const UGenericWidget* InWidget) const
{
	if (!IsValid(InWidget))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWidget Is InValid"))
		return nullptr;
	}

	return GetSlot(InWidget->SlotTag);
}

UGameplayTagSlot* UGenericGameSlotSubsystem::GetSlot(const FGameplayTag InSlotTag) const
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

UGenericWidget* UGenericGameSlotSubsystem::GetSlotWidget(FGameplayTag InSlotTag) const
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

TArray<UGenericWidget*> UGenericGameSlotSubsystem::GetSlotWidgets() const
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

bool UGenericGameSlotSubsystem::AddSlotWidget(UGenericWidget* InWidget)
{
	/* Check Is Valid Slot Tag */
	if (InWidget->SlotTag.IsValid())
	{
		/* If Valid, Find The Valid GameplayTagSlot And Add Widget To It */
		if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
		{
			Slot->AddChild(InWidget);
			return true;
		}
		/* Otherwise Is Error */
		else
		{
			GenericLOG(GenericLogUI, Warning, TEXT("Slot Is InValid"))
		}
	}
	else
	{
		/* If Not Valid, Check Is a GameHUD Class, If True, Add Widget To Viewport */
		if (UGenericGameHUD* GameHUD = Cast<UGenericGameHUD>(InWidget))
		{
			InWidget->AddToViewport(GameHUD->ViewportZOrder);
			return true;
		}
		/* if Not Valid SlotTag And Also Not a GameHUD Class, Check The Widget Outer Is Also a Generic Widget, If True, Add Widget To Outer Widget */
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

void UGenericGameSlotSubsystem::RemoveSlotWidget(UGenericWidget* InWidget)
{
	if (IsValid(InWidget))
	{
		InWidget->RemoveFromParent();
	}
}
