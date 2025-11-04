// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_LevelStreaming.h"

#include "LevelStreamingSubsystem.h"


void UBPFunctions_LevelStreaming::LoadLevel(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->LoadLevel(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::LoadLevels(const UObject* WorldContextObject, const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->LoadLevels(Levels, bMakeVisibleAfterLoad, bShouldBlockOnLoad, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::LoadLevelsBySetting(const UObject* WorldContextObject, const TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->LoadLevelsBySetting(LoadLevelStreamingSettings, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnloadLevel(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level, const bool bShouldBlockOnUnload, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->UnloadLevel(Level, bShouldBlockOnUnload, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnloadLevels(const UObject* WorldContextObject, const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->UnloadLevels(Levels, bShouldBlockOnUnload, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnloadLevelsBySetting(const UObject* WorldContextObject, const TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->UnloadLevelsBySetting(UnloadLevelStreamingSettings, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::SetLevelVisibility(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level, const bool bVisible, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->SetLevelVisibility(Level, bVisible, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::SetLevelsVisibility(const UObject* WorldContextObject, const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->SetLevelsVisibility(Levels, bVisible, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::LoadCurrentWorldLevelStreaming(const UObject* WorldContextObject, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->LoadCurrentWorldLevelStreaming(HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnLoadCurrentWorldLevelStreaming(const UObject* WorldContextObject, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		const auto HandleOnceFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnOnceFinish]()
			{
				OnOnceFinish.ExecuteIfBound();
			}
		);

		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingSubsystem->UnLoadCurrentWorldLevelStreaming(HandleOnceFinish, HandleFinish);
	}
}

ULevelStreaming* UBPFunctions_LevelStreaming::GetLevelStreaming(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level)
{
	if (const ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		return LevelStreamingSubsystem->GetLevelStreaming(Level);
	}
	return nullptr;
}

bool UBPFunctions_LevelStreaming::IsLevelLoaded(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level)
{
	if (const ULevelStreaming* LevelStreaming = GetLevelStreaming(WorldContextObject, Level))
	{
		return LevelStreaming->IsLevelLoaded();
	}
	return false;
}

bool UBPFunctions_LevelStreaming::IsCurrentWorldContainLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool& Contain)
{
	if (const ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		Contain = LevelStreamingSubsystem->IsCurrentWorldContainLevel(Level);
		return true;
	}
	return false;
}
