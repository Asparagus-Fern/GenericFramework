// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_GameHUD.h"

#include "GenericHUDManager.h"
#include "Manager/ManagerStatics.h"

/* ==================== UGameplayTagSlot ==================== */

void UBPFunctions_GameHUD::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (UGenericHUDManager* GameHUDManager = GetManager<UGenericHUDManager>())
	{
		GameHUDManager->RegisterSlot(InSlot);
	}
}

void UBPFunctions_GameHUD::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (UGenericHUDManager* GameHUDManager = GetManager<UGenericHUDManager>())
	{
		GameHUDManager->UnRegisterSlot(InSlot);
	}
}

bool UBPFunctions_GameHUD::GetSlots(TArray<UGameplayTagSlot*>& Slots)
{
	if (UGenericHUDManager* GameHUDManager = GetManager<UGenericHUDManager>())
	{
		Slots = GameHUDManager->GetSlots();
		return true;
	}

	return false;
}

UGameplayTagSlot* UBPFunctions_GameHUD::GetSlot(FGameplayTag InSlotTag)
{
	if (const UGenericHUDManager* GameHUDManager = GetManager<UGenericHUDManager>())
	{
		return GameHUDManager->GetSlot(InSlotTag);
	}

	return nullptr;
}
