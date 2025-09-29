// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_GameHUD.h"

#include "GenericGameHUDManager.h"
#include "Manager/ManagerStatics.h"

void UBPFunctions_GameHUD::CreateGameHUDListBySoftClass(const TArray<TSoftClassPtr<UGenericGameHUD>>& InGameHUDClasses)
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->CreateGameHUDs(InGameHUDClasses);
	}
}

void UBPFunctions_GameHUD::CreateGameHUDListByClass(TArray<TSubclassOf<UGenericGameHUD>> InGameHUDClasses)
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->CreateGameHUDs(InGameHUDClasses);
	}
}

void UBPFunctions_GameHUD::CreateGameHUDList(TArray<UGenericGameHUD*> InGameHUDs)
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->CreateGameHUDs(InGameHUDs);
	}
}

void UBPFunctions_GameHUD::CreateGameHUD(UGenericGameHUD* InGameHUD)
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->CreateGameHUD(InGameHUD);
	}
}

void UBPFunctions_GameHUD::RemoveGameHUDList(TArray<UGenericGameHUD*> InGameHUDs)
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->RemoveGameHUDs(InGameHUDs);
	}
}

void UBPFunctions_GameHUD::RemoveGameHUD(UGenericGameHUD* InGameHUD)
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->RemoveGameHUD(InGameHUD);
	}
}

void UBPFunctions_GameHUD::ClearAllGameHUD()
{
	if (UGenericGameHUDManager* GameHUDManager = GetManagerOwner<UGenericGameHUDManager>())
	{
		GameHUDManager->ClearGameHUDs();
	}
}
