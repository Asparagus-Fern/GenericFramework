// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_GameSlot.h"

#include "GenericGameSlotSubsystem.h"
#include "Base/GenericWidget.h"

/* ==================== UGameplayTagSlot ==================== */

void UBPFunctions_GameSlot::RegisterSlot(const UObject* WorldContextObject, UGameplayTagSlot* InSlot)
{
	if (UGenericGameSlotSubsystem* GameHUDManager = UGenericGameSlotSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->RegisterSlot(InSlot);
	}
}

void UBPFunctions_GameSlot::UnRegisterSlot(const UObject* WorldContextObject, UGameplayTagSlot* InSlot)
{
	if (UGenericGameSlotSubsystem* GameHUDManager = UGenericGameSlotSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->UnRegisterSlot(InSlot);
	}
}

UGameplayTagSlot* UBPFunctions_GameSlot::GetSlot(const UObject* WorldContextObject, FGameplayTag InTag)
{
	if (UGenericGameSlotSubsystem* GameHUDManager = UGenericGameSlotSubsystem::Get(WorldContextObject))
	{
		return GameHUDManager->GetSlot(InTag);
	}

	return nullptr;
}

UGenericWidget* UBPFunctions_GameSlot::GetSlotWidget(const UObject* WorldContextObject, TSubclassOf<UGenericWidget> InClass, FGameplayTag InTag)
{
	ensure(InClass);

	if (UGenericGameSlotSubsystem* GameHUDManager = UGenericGameSlotSubsystem::Get(WorldContextObject))
	{
		return GameHUDManager->GetSlotWidget(InTag);
	}

	return nullptr;
}
