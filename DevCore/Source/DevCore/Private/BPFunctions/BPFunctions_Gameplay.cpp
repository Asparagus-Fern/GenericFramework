// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Gameplay.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"

UGameInstance* UBPFunctions_Gameplay::GetGameInstanceByClass(const UObject* WorldContextObject, const TSubclassOf<UGameInstance> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance<UGameInstance>();
	}

	return nullptr;
}

AGameModeBase* UBPFunctions_Gameplay::GetGameModeByClass(const UObject* WorldContextObject, const TSubclassOf<AGameModeBase> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetAuthGameMode<AGameModeBase>();
	}

	return nullptr;
}

AGameStateBase* UBPFunctions_Gameplay::GetGameStateByClass(const UObject* WorldContextObject, const TSubclassOf<AGameStateBase> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameState<AGameStateBase>();
	}

	return nullptr;
}

AHUD* UBPFunctions_Gameplay::GetHUDByClass(const UObject* WorldContextObject, const TSubclassOf<AHUD> InClass)
{
	ensure(InClass);

	if (const APlayerController* PC = GetPlayerControllerByClass(WorldContextObject, APlayerController::StaticClass()))
	{
		return PC->GetHUD<AHUD>();
	}

	return nullptr;
}

APawn* UBPFunctions_Gameplay::GetPawnByClass(const UObject* WorldContextObject, const TSubclassOf<APawn> InClass)
{
	ensure(InClass);

	if (const APlayerController* PC = GetPlayerControllerByClass(WorldContextObject, APlayerController::StaticClass()))
	{
		return PC->GetPawn<APawn>();
	}

	return nullptr;
}

APlayerController* UBPFunctions_Gameplay::GetPlayerControllerByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerController> InClass)
{
	ensure(InClass);

	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetFirstPlayerController<APlayerController>();
	}

	return nullptr;
}

APlayerState* UBPFunctions_Gameplay::GetPlayerStateByClass(const UObject* WorldContextObject, const TSubclassOf<APlayerState> InClass)
{
	ensure(InClass);

	if (const APlayerController* PC = GetPlayerControllerByClass(WorldContextObject, APlayerController::StaticClass()))
	{
		return PC->GetPlayerState<APlayerState>();
	}

	return nullptr;
}
