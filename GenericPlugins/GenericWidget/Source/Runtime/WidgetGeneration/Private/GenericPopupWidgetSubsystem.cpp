// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericPopupWidgetSubsystem.h"

#include "GenericGameSlotSubsystem.h"
#include "GenericWidgetSubsystem.h"
#include "Base/GenericPopupWidget.h"
#include "UWidget/GameplayTagSlot.h"

UGenericPopupWidgetSubsystem* UGenericPopupWidgetSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UGenericPopupWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGenericWidgetSubsystem::Delegate_PostWidgetOpened.AddUObject(this, &UGenericPopupWidgetSubsystem::PostWidgetOpened);
	UGenericWidgetSubsystem::Delegate_PostWidgetClosed.AddUObject(this, &UGenericPopupWidgetSubsystem::PostWidgetClosed);
}

void UGenericPopupWidgetSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UGenericWidgetSubsystem::Delegate_PostWidgetOpened.RemoveAll(this);
	UGenericWidgetSubsystem::Delegate_PostWidgetClosed.RemoveAll(this);
}

void UGenericPopupWidgetSubsystem::PostWidgetOpened(UGenericWidget* InWidget)
{
	if (UGenericPopupWidget* PopupWidget = Cast<UGenericPopupWidget>(InWidget))
	{
		if (PopupWidget->bBreakGameInput)
		{
			if (UGenericGameSlotSubsystem* GameSlotSubsystem = UGenericGameSlotSubsystem::Get(this))
			{
				if (UGameplayTagSlot* GameSlot = GameSlotSubsystem->GetSlot(TAG_GameHUD_Game))
				{
					GameSlot->SetVisibility(ESlateVisibility::HitTestInvisible);
				}
			}


			BreakGameSlotPopupWidgets.Add(PopupWidget);
		}
	}
}

void UGenericPopupWidgetSubsystem::PostWidgetClosed(UGenericWidget* InWidget)
{
	if (UGenericPopupWidget* PopupWidget = Cast<UGenericPopupWidget>(InWidget))
	{
		if (BreakGameSlotPopupWidgets.Contains(PopupWidget))
		{
			BreakGameSlotPopupWidgets.Remove(PopupWidget);
		}

		if (BreakGameSlotPopupWidgets.IsEmpty())
		{
			if (UGenericGameSlotSubsystem* GameSlotSubsystem = UGenericGameSlotSubsystem::Get(this))
			{
				if (UGameplayTagSlot* GameSlot = GameSlotSubsystem->GetSlot(TAG_GameHUD_Game))
				{
					GameSlot->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				}
			}
		}
	}
}
