// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericSaveGameSubsystem.h"

#include "GenericSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Type/DebugType.h"

UGenericSaveGameSubsystem* UGenericSaveGameSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance()->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UGenericSaveGameSubsystem::AsyncSaveGame(const FSaveGameParameter& Parameter)
{
	if (!Parameter.CanSave())
	{
		GenericLOG(GenericLogSaveGame, Error, TEXT("Parameter Is InValid"))
		return;
	}

	if (SaveGameParameters.Contains(Parameter))
	{
		GenericLOG(GenericLogSaveGame, Warning, TEXT("Parameter Is Saving"))
		return;
	}

	SaveGameParameters.Add(Parameter);

	FAsyncSaveGameToSlotDelegate SavedDelegate;
	SavedDelegate.BindUObject(this, &UGenericSaveGameSubsystem::OnAsyncSaveGameCompleted);
	UGameplayStatics::AsyncSaveGameToSlot(Parameter.SaveGame, Parameter.GetSaveGameSlotName(), Parameter.UserIndex);
}

void UGenericSaveGameSubsystem::OnAsyncSaveGameCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (SaveGameParameters.Contains(SlotName))
	{
		FSaveGameParameter Parameter = *SaveGameParameters.FindByKey(SlotName);
		SaveGameParameters.Remove(Parameter);

		if (Parameter.bIsAutoSave)
		{
			AutoSaveParameters.AddUnique(Parameter);
		}

		if (bSuccess)
		{
			Parameter.OnSuccess();
			Parameter.SaveGame->OnSaved();
		}
		else
		{
			Parameter.OnFail();
		}
	}
}

void UGenericSaveGameSubsystem::AsyncLoadGame(const FSaveGameParameter& Parameter)
{
	if (!Parameter.CanLoad())
	{
		GenericLOG(GenericLogSaveGame, Error, TEXT("Parameter Is InValid"))
		return;
	}

	if (LoadGameParameters.Contains(Parameter))
	{
		GenericLOG(GenericLogSaveGame, Warning, TEXT("Parameter Is Loading"))
		return;
	}

	LoadGameParameters.Add(Parameter);

	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &UGenericSaveGameSubsystem::OnAsyncLoadGameCompleted);
	UGameplayStatics::AsyncLoadGameFromSlot(Parameter.GetSaveGameSlotName(), Parameter.UserIndex, LoadDelegate);
}

void UGenericSaveGameSubsystem::OnAsyncLoadGameCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	if (LoadGameParameters.Contains(SlotName))
	{
		FSaveGameParameter Parameter = *LoadGameParameters.FindByKey(SlotName);
		Parameter.SaveGame = Cast<UGenericSaveGame>(SaveGame);
		LoadGameParameters.Remove(Parameter);

		if (Parameter.CheckIsValid())
		{
			Parameter.OnSuccess();
			Parameter.SaveGame->OnLoaded();
		}
		else
		{
			Parameter.OnFail();
		}
	}
}

void UGenericSaveGameSubsystem::StartAutoSaveGame()
{
	// GetWorld()
}

void UGenericSaveGameSubsystem::StopAutoSaveGame()
{
}
