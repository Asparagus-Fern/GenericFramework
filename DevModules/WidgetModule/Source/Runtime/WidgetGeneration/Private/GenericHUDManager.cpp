// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericHUDManager.h"

#include "GenericWidgetSettings.h"
#include "GenericWidgetManager.h"
#include "Base/GenericHUD.h"
#include "Base/GenericWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Manager/ManagerStatics.h"
#include "StaticFunctions/StaticFunctions_Object.h"
#include "UWidget/GameplayTagSlot.h"

bool UGenericHUDManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericHUDManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGameplayTagSlot::OnBuildGameplayTagSlot.AddUObject(this, &UGenericHUDManager::RegisterSlot);
	UGameplayTagSlot::OnRemoveGameplayTagSlot.AddUObject(this, &UGenericHUDManager::UnRegisterSlot);

	UGenericWidgetManager::Delegate_PreWidgetOpened.AddUObject(this, &UGenericHUDManager::PreWidgetOpened);
	UGenericWidgetManager::Delegate_OnWidgetOpened.AddUObject(this, &UGenericHUDManager::OnWidgetOpened);

	UGenericWidgetManager::Delegate_PreWidgetClosed.AddUObject(this, &UGenericHUDManager::PreWidgetClosed);
	UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(this, &UGenericHUDManager::PostWidgetClosed);

	RegisterManager(this);
}

void UGenericHUDManager::Deinitialize()
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

bool UGenericHUDManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGenericHUDManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);

	if (UGenericWidgetSettings::Get()->AutoCreateGameHUD)
	{
		BROADCAST_UNIFIED_DELEGATE(Delegate_PreHUDCreated, BPDelegate_PreHUDCreated);
		CreateGameHUDs(UGenericWidgetSettings::Get()->GenericHUDClasses);
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostHUDCreated, BPDelegate_PostHUDCreated);
	}
}

void UGenericHUDManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	Slots.Reset();
	GameHUDs.Reset();
}

/* ==================== DelegateBinding ==================== */

void UGenericHUDManager::PreWidgetOpened(FOpenWidgetParameter& Parameter)
{
	if (Parameter.WidgetToHandle.IsA<UGenericHUD>())
	{
		Parameter.bAddToViewport = !Parameter.WidgetToHandle->SlotTag.IsValid();
	}

	if (Parameter.SlotTag.IsValid())
	{
		Parameter.Slot = GetSlot(Parameter.SlotTag);
		Parameter.WidgetToRemove = GetSlotWidget(Parameter.SlotTag);
	}
}

void UGenericHUDManager::OnWidgetOpened(const FOpenWidgetParameter& Parameter)
{
	if (Parameter.bAddToViewport)
	{
		UGenericHUD* GameHUD = Cast<UGenericHUD>(Parameter.WidgetToHandle);
		if (IsValid(GameHUD))
		{
			Parameter.WidgetToHandle->AddToViewport(GameHUD->ViewportZOrder);
		}
		else
		{
			Parameter.WidgetToHandle->AddToViewport();
		}
	}
	else
	{
		AddSlotWidget(Parameter.WidgetToHandle);
	}
}

void UGenericHUDManager::PreWidgetClosed(FCloseWidgetParameter& Parameter)
{
	Parameter.Slot = GetSlot(Parameter.SlotTag);

	if (!Parameter.WidgetToHandle)
	{
		Parameter.WidgetToHandle = GetSlotWidget(Parameter.SlotTag);
	}
}

void UGenericHUDManager::PostWidgetClosed(UGenericWidget* InWidget)
{
	InWidget->RemoveFromParent();
}

/* ==================== UGameplayTagSlot ==================== */

void UGenericHUDManager::RegisterSlot(UGameplayTagSlot* InSlot)
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

void UGenericHUDManager::UnRegisterSlot(UGameplayTagSlot* InSlot)
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

UGameplayTagSlot* UGenericHUDManager::GetSlot(const UGenericWidget* InWidget) const
{
	if (!IsValid(InWidget))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWidget Is InValid"))
		return nullptr;
	}

	return GetSlot(InWidget->SlotTag);
}

UGameplayTagSlot* UGenericHUDManager::GetSlot(const FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("SlotTag Is InValid"))
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

UGenericWidget* UGenericHUDManager::GetSlotWidget(FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("SlotTag Is InValid"))
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

TArray<UGenericWidget*> UGenericHUDManager::GetSlotWidgets() const
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

bool UGenericHUDManager::AddSlotWidget(UGenericWidget* InWidget) const
{
	if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
	{
		return IsValid(Slot->AddChild(InWidget));
	}

	return false;
}

bool UGenericHUDManager::RemoveSlotWidget(UGenericWidget* InWidget) const
{
	if (UGameplayTagSlot* Slot = GetSlot(InWidget->SlotTag))
	{
		return Slot->RemoveChild(InWidget);
	}

	return false;
}

/* ==================== Game HUD ==================== */

void UGenericHUDManager::CreateGameHUDs(const TArray<TSoftClassPtr<UGenericHUD>>& InGameHUDClasses)
{
	CreateGameHUDs(FStaticFunctions_Object::LoadClass<UGenericHUD>(InGameHUDClasses));
}

void UGenericHUDManager::CreateGameHUDs(TArray<TSubclassOf<UGenericHUD>> InGameHUDClasses)
{
	for (const auto& GameHUDClass : InGameHUDClasses)
	{
		if (!IsValid(GameHUDClass))
		{
			GenericLOG(GenericLogUI, Error, TEXT("GameHUDClass Is Invalid"))
			continue;
		}

		CreateGameHUD(CreateWidget<UGenericHUD>(GetWorld(), GameHUDClass));
	}
}

void UGenericHUDManager::CreateGameHUDs(TArray<UGenericHUD*> InGameHUDs)
{
	for (const auto& GameHUD : InGameHUDs)
	{
		CreateGameHUD(GameHUD);
	}
}

void UGenericHUDManager::CreateGameHUD(UGenericHUD* InGameHUD)
{
	if (!IsValid(InGameHUD))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InGameHUD Is Invalid"))
		return;
	}

	if (!InGameHUD->HUDTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("HUD Tag Is Invalid"))
		return;
	}

	if (GameHUDs.Contains(InGameHUD->HUDTag))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InGameHUD Is Already Add To Viewport"))
		return;
	}

	GameHUDs.Add(InGameHUD->HUDTag, InGameHUD);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDCreated, BPDelegate_OnHUDCreated, InGameHUD);
	GetManager<UGenericWidgetManager>()->OpenUserWidget(InGameHUD);
}

void UGenericHUDManager::RemoveGameHUDs(TArray<FGameplayTag> InHUDTags)
{
	for (auto& InHUDTag : InHUDTags)
	{
		RemoveGameHUD(InHUDTag);
	}
}

void UGenericHUDManager::RemoveGameHUD(const FGameplayTag InHUDTag)
{
	TArray<TObjectPtr<UGenericHUD>> Values;
	GameHUDs.GenerateValueArray(Values);

	if (TObjectPtr<UGenericHUD>* Found = Values.FindByPredicate([InHUDTag](const TObjectPtr<UGenericHUD>& InGameHUD)
		{
			return InGameHUD->HUDTag == InHUDTag;
		}
	))
	{
		RemoveGameHUD(*Found);
	}
}

void UGenericHUDManager::RemoveGameHUDs(TArray<UGenericHUD*> InGameHUDs)
{
	for (auto& InGameHUD : InGameHUDs)
	{
		RemoveGameHUD(InGameHUD);
	}
}

void UGenericHUDManager::RemoveGameHUD(UGenericHUD* InGameHUD)
{
	if (!IsValid(InGameHUD))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InGameHUD Is Invalid"))
		return;
	}

	if (!InGameHUD->HUDTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("HUD Tag Is Invalid"))
		return;
	}

	if (!GameHUDs.Contains(InGameHUD->HUDTag))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InGameHUD Is Already Remove From Viewport"))
		return;
	}

	InGameHUD->WidgetTree->ForEachWidget([](UWidget* Widget)
		{
		}
	);

	GetManager<UGenericWidgetManager>()->CloseUserWidget(InGameHUD);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDDestroyed, BPDelegate_OnHUDDestroyed, InGameHUD);
	GameHUDs.Remove(InGameHUD->HUDTag);
}

void UGenericHUDManager::ClearGameHUDs()
{
	TArray<TObjectPtr<UGenericHUD>> Values;
	GameHUDs.GenerateValueArray(Values);

	for (const auto& GameHUD : Values)
	{
		RemoveGameHUD(GameHUD);
	}
}

UGenericHUD* UGenericHUDManager::GetGameHUDByTag(const FGameplayTag InHUDTag) const
{
	if (GameHUDs.Contains(InHUDTag))
	{
		return GameHUDs.FindRef(InHUDTag);
	}

	return nullptr;
}

TArray<UGenericHUD*> UGenericHUDManager::GetGameHUDsByTag(const FGameplayTag InHUDTag)
{
	TArray<UGenericHUD*> Result;
	for (auto& GameHUD : GameHUDs)
	{
		if (GameHUD.Value->HUDTag.MatchesTag(InHUDTag))
		{
			Result.Add(GameHUD.Value);
		}
	}
	return Result;
}
