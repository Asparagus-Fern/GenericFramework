// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_GameSlot.h"

#include "GenericGameSlotManager.h"
#include "Manager/ManagerStatics.h"

/* ==================== UGameplayTagSlot ==================== */

void UBPFunctions_GameSlot::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (UGenericGameSlotManager* GameHUDManager = GetManagerOwner<UGenericGameSlotManager>())
	{
		GameHUDManager->RegisterSlot(InSlot);
	}
}

void UBPFunctions_GameSlot::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (UGenericGameSlotManager* GameHUDManager = GetManagerOwner<UGenericGameSlotManager>())
	{
		GameHUDManager->UnRegisterSlot(InSlot);
	}
}
