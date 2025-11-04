// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericGameHUDSubsystem.h"

#include "GameHUDSettings.h"
#include "GenericWidgetSubsystem.h"
#include "Base/GenericGameHUD.h"
#include "Base/GenericWidget.h"
#include "Blueprint/WidgetTree.h"

#include "StaticFunctions/StaticFunctions_Object.h"
#include "Type/GenericType.h"

UGenericGameHUDSubsystem* UGenericGameHUDSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UGenericGameHUDSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGenericWidgetSubsystem::Delegate_OnWidgetOpened.AddUObject(this, &UGenericGameHUDSubsystem::OnWidgetOpened);
	UGenericWidgetSubsystem::Delegate_PostWidgetClosed.AddUObject(this, &UGenericGameHUDSubsystem::PostWidgetClosed);
}

void UGenericGameHUDSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (UGameHUDSettings::Get()->AutoCreateGameHUD)
	{
		BROADCAST_UNIFIED_DELEGATE(Delegate_PreHUDCreated, BPDelegate_PreHUDCreated);

		for (const auto& HUDSoftClass : UGameHUDSettings::Get()->GenericHUDClasses)
		{
			if (TSubclassOf<UGenericGameHUD> HUDClass = FStaticFunctions_Object::LoadClass<UGenericGameHUD>(HUDSoftClass))
			{
				CreateGameHUD(CreateWidget<UGenericGameHUD>(GetWorld(), HUDClass));
			}
		}

		BROADCAST_UNIFIED_DELEGATE(Delegate_PostHUDCreated, BPDelegate_PostHUDCreated);
	}
}

void UGenericGameHUDSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UGenericWidgetSubsystem::Delegate_OnWidgetOpened.RemoveAll(this);
	UGenericWidgetSubsystem::Delegate_PostWidgetClosed.RemoveAll(this);

	GameHUDs.Reset();
}

void UGenericGameHUDSubsystem::OnWidgetOpened(FOpenWidgetParameter& Parameter)
{
	if (UGenericGameHUD* GameHUD = Cast<UGenericGameHUD>(Parameter.WidgetToHandle))
	{
		GameHUDs.Add(GameHUD);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDCreated, BPDelegate_OnHUDCreated, GameHUD);
	}
}

void UGenericGameHUDSubsystem::PostWidgetClosed(UGenericWidget* InWidget)
{
	if (UGenericGameHUD* GameHUD = Cast<UGenericGameHUD>(InWidget))
	{
		GameHUDs.Remove(GameHUD);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnHUDDestroyed, BPDelegate_OnHUDDestroyed, GameHUD);
	}
}

/* ==================== Game HUD ==================== */

void UGenericGameHUDSubsystem::CreateGameHUDs(TArray<UGenericGameHUD*> InGameHUDs)
{
	for (const auto& GameHUD : InGameHUDs)
	{
		CreateGameHUD(GameHUD);
	}
}

void UGenericGameHUDSubsystem::CreateGameHUD(UGenericGameHUD* InGameHUD)
{
	if (!IsValid(InGameHUD))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InGameHUD Is Invalid"))
		return;
	}

	if (GameHUDs.Contains(InGameHUD))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InGameHUD Is Already Add To Viewport"))
		return;
	}

	UGenericWidgetSubsystem::Get(this)->OpenGenericWidget(InGameHUD);
}

void UGenericGameHUDSubsystem::RemoveGameHUDs(TArray<UGenericGameHUD*> InGameHUDs)
{
	for (auto& InGameHUD : InGameHUDs)
	{
		RemoveGameHUD(InGameHUD);
	}
}

void UGenericGameHUDSubsystem::RemoveGameHUD(UGenericGameHUD* InGameHUD)
{
	if (!IsValid(InGameHUD))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InGameHUD Is Invalid"))
		return;
	}

	if (!GameHUDs.Contains(InGameHUD))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InGameHUD Is Already Remove From Viewport"))
		return;
	}

	UGenericWidgetSubsystem::Get(this)->CloseGenericWidget(InGameHUD);
}

void UGenericGameHUDSubsystem::ClearGameHUDs()
{
	TArray<TObjectPtr<UGenericGameHUD>> TempGameHUDs = GameHUDs;
	for (const auto& GameHUD : TempGameHUDs)
	{
		RemoveGameHUD(GameHUD);
	}
}
