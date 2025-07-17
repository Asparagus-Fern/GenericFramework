// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericGameHUDManager.h"

#include "GenericWidgetSettings.h"
#include "GenericWidgetManager.h"
#include "Base/GenericGameHUD.h"
#include "Base/GenericWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Manager/ManagerStatics.h"
#include "StaticFunctions/StaticFunctions_Object.h"
#include "UWidget/GameplayTagSlot.h"

bool UGenericGameHUDManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericGameHUDManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGenericWidgetManager::Delegate_OnWidgetOpened.AddUObject(this, &UGenericGameHUDManager::OnWidgetOpened);
	UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(this, &UGenericGameHUDManager::PostWidgetClosed);

	RegisterManager(this);
}

void UGenericGameHUDManager::Deinitialize()
{
	Super::Deinitialize();

	UGenericWidgetManager::Delegate_OnWidgetOpened.RemoveAll(this);
	UGenericWidgetManager::Delegate_PostWidgetClosed.RemoveAll(this);

	UnRegisterManager();
}

bool UGenericGameHUDManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGenericGameHUDManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);

	if (UGenericWidgetSettings::Get()->AutoCreateGameHUD)
	{
		BROADCAST_UNIFIED_DELEGATE(Delegate_PreHUDCreated, BPDelegate_PreHUDCreated);
		CreateGameHUDs(UGenericWidgetSettings::Get()->GenericHUDClasses);
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostHUDCreated, BPDelegate_PostHUDCreated);
	}
}

void UGenericGameHUDManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	GameHUDs.Reset();
}

void UGenericGameHUDManager::OnWidgetOpened(FOpenWidgetParameter& Parameter)
{
	if (UGenericGameHUD* GameHUD = Cast<UGenericGameHUD>(Parameter.WidgetToHandle))
	{
		GameHUDs.Add(GameHUD);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDCreated, BPDelegate_OnHUDCreated, GameHUD);
	}
}

void UGenericGameHUDManager::PostWidgetClosed(UGenericWidget* InWidget)
{
	if (UGenericGameHUD* GameHUD = Cast<UGenericGameHUD>(InWidget))
	{
		GameHUDs.Remove(GameHUD);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDDestroyed, BPDelegate_OnHUDDestroyed, GameHUD);
	}
}

/* ==================== Game HUD ==================== */

void UGenericGameHUDManager::CreateGameHUDs(const TArray<TSoftClassPtr<UGenericGameHUD>>& InGameHUDClasses)
{
	CreateGameHUDs(FStaticFunctions_Object::LoadClass<UGenericGameHUD>(InGameHUDClasses));
}

void UGenericGameHUDManager::CreateGameHUDs(TArray<TSubclassOf<UGenericGameHUD>> InGameHUDClasses)
{
	for (const auto& GameHUDClass : InGameHUDClasses)
	{
		if (!IsValid(GameHUDClass))
		{
			GenericLOG(GenericLogUI, Error, TEXT("GameHUDClass Is Invalid"))
			continue;
		}

		CreateGameHUD(CreateWidget<UGenericGameHUD>(GetWorld(), GameHUDClass));
	}
}

void UGenericGameHUDManager::CreateGameHUDs(TArray<UGenericGameHUD*> InGameHUDs)
{
	for (const auto& GameHUD : InGameHUDs)
	{
		CreateGameHUD(GameHUD);
	}
}

void UGenericGameHUDManager::CreateGameHUD(UGenericGameHUD* InGameHUD)
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

	if (GameHUDs.Contains(InGameHUD))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InGameHUD Is Already Add To Viewport"))
		return;
	}

	GetManager<UGenericWidgetManager>()->OpenUserWidget(InGameHUD);
}

void UGenericGameHUDManager::RemoveGameHUDs(TArray<UGenericGameHUD*> InGameHUDs)
{
	for (auto& InGameHUD : InGameHUDs)
	{
		RemoveGameHUD(InGameHUD);
	}
}

void UGenericGameHUDManager::RemoveGameHUD(UGenericGameHUD* InGameHUD)
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

	if (!GameHUDs.Contains(InGameHUD))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InGameHUD Is Already Remove From Viewport"))
		return;
	}

	GetManager<UGenericWidgetManager>()->CloseUserWidget(InGameHUD);
}

void UGenericGameHUDManager::ClearGameHUDs()
{
	TArray<TObjectPtr<UGenericGameHUD>> TempGameHUDs = GameHUDs;
	for (const auto& GameHUD : TempGameHUDs)
	{
		RemoveGameHUD(GameHUD);
	}
}
