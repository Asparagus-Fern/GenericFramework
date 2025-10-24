// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "GenericPopupWidgetManager.h"

#include "GenericGameSlotManager.h"
#include "GenericWidgetManager.h"
#include "Base/GenericPopupWidget.h"
#include "UWidget/GameplayTagSlot.h"

bool UGenericPopupWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
}

void UGenericPopupWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGenericWidgetManager::Delegate_PostWidgetOpened.AddUObject(this, &UGenericPopupWidgetManager::PostWidgetOpened);
	UGenericWidgetManager::Delegate_PostWidgetClosed.AddUObject(this, &UGenericPopupWidgetManager::PostWidgetClosed);

	RegisterManager(this);
}

void UGenericPopupWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UGenericWidgetManager::Delegate_PostWidgetOpened.RemoveAll(this);
	UGenericWidgetManager::Delegate_PostWidgetClosed.RemoveAll(this);
}

bool UGenericPopupWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGenericPopupWidgetManager::PostWidgetOpened(UGenericWidget* InWidget)
{
	if (UGenericPopupWidget* PopupWidget = Cast<UGenericPopupWidget>(InWidget))
	{
		if (PopupWidget->bBreakGameInput)
		{
			if (UGameplayTagSlot* GameSlot = FGameSlotHelper::GetSlot(TAG_GameHUD_Game))
			{
				GameSlot->SetVisibility(ESlateVisibility::HitTestInvisible);
			}

			BreakGameSlotPopupWidgets.Add(PopupWidget);
		}
	}
}

void UGenericPopupWidgetManager::PostWidgetClosed(UGenericWidget* InWidget)
{
	if (UGenericPopupWidget* PopupWidget = Cast<UGenericPopupWidget>(InWidget))
	{
		if (BreakGameSlotPopupWidgets.Contains(PopupWidget))
		{
			BreakGameSlotPopupWidgets.Remove(PopupWidget);
		}

		if (BreakGameSlotPopupWidgets.IsEmpty())
		{
			if (UGameplayTagSlot* GameSlot = FGameSlotHelper::GetSlot(TAG_GameHUD_Game))
			{
				GameSlot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
		}
	}
}
