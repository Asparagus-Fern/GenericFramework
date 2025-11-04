// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_GameHUD.h"

#include "GenericGameHUDSubsystem.h"

void UBPFunctions_GameHUD::CreateGameHUDList(const UObject* WorldContextObject, TArray<UGenericGameHUD*> InGameHUDs)
{
	if (UGenericGameHUDSubsystem* GameHUDManager = UGenericGameHUDSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->CreateGameHUDs(InGameHUDs);
	}
}

void UBPFunctions_GameHUD::CreateGameHUD(const UObject* WorldContextObject, UGenericGameHUD* InGameHUD)
{
	if (UGenericGameHUDSubsystem* GameHUDManager = UGenericGameHUDSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->CreateGameHUD(InGameHUD);
	}
}

void UBPFunctions_GameHUD::RemoveGameHUDList(const UObject* WorldContextObject, TArray<UGenericGameHUD*> InGameHUDs)
{
	if (UGenericGameHUDSubsystem* GameHUDManager = UGenericGameHUDSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->RemoveGameHUDs(InGameHUDs);
	}
}

void UBPFunctions_GameHUD::RemoveGameHUD(const UObject* WorldContextObject, UGenericGameHUD* InGameHUD)
{
	if (UGenericGameHUDSubsystem* GameHUDManager = UGenericGameHUDSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->RemoveGameHUD(InGameHUD);
	}
}

void UBPFunctions_GameHUD::ClearAllGameHUD(const UObject* WorldContextObject)
{
	if (UGenericGameHUDSubsystem* GameHUDManager = UGenericGameHUDSubsystem::Get(WorldContextObject))
	{
		GameHUDManager->ClearGameHUDs();
	}
}
