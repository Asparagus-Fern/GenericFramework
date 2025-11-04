// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_GameSlot.h"

#include "GenericGameSlotSubsystem.h"

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
