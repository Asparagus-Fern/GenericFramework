// Fill out your copyright notice in the Description page of Project Settings.

#include "BPFunctions_GameHUD.h"

#include "GameHUDManager.h"
#include "Manager/ManagerStatics.h"

/* ==================== UGameplayTagSlot ==================== */

void UBPFunctions_GameHUD::RegisterSlot(UGameplayTagSlot* InSlot)
{
	if (UGameHUDManager* GameHUDManager = GetManager<UGameHUDManager>())
	{
		GameHUDManager->RegisterSlot(InSlot);
	}
}

void UBPFunctions_GameHUD::UnRegisterSlot(UGameplayTagSlot* InSlot)
{
	if (UGameHUDManager* GameHUDManager = GetManager<UGameHUDManager>())
	{
		GameHUDManager->UnRegisterSlot(InSlot);
	}
}

bool UBPFunctions_GameHUD::GetSlots(TArray<UGameplayTagSlot*>& Slots)
{
	if (UGameHUDManager* GameHUDManager = GetManager<UGameHUDManager>())
	{
		Slots = GameHUDManager->GetSlots();
		return true;
	}

	return false;
}

UGameplayTagSlot* UBPFunctions_GameHUD::GetSlot(const FGameplayTag InSlotTag)
{
	if (const UGameHUDManager* GameHUDManager = GetManager<UGameHUDManager>())
	{
		return GameHUDManager->GetSlot(InSlotTag);
	}

	return nullptr;
}
