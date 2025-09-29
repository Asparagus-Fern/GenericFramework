// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_LevelStreaming.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerStatics.h"

void UBPFunctions_LevelStreaming::LoadLevel(const TSoftObjectPtr<UWorld> Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingManager->LoadLevel(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::LoadLevels(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->LoadLevels(Levels, bMakeVisibleAfterLoad, bShouldBlockOnLoad, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::LoadLevelsBySetting(const TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->LoadLevelsBySetting(LoadLevelStreamingSettings, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnloadLevel(const TSoftObjectPtr<UWorld> Level, const bool bShouldBlockOnUnload, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingManager->UnloadLevel(Level, bShouldBlockOnUnload, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnloadLevels(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->UnloadLevels(Levels, bShouldBlockOnUnload, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnloadLevelsBySetting(const TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->UnloadLevelsBySetting(UnloadLevelStreamingSettings, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::SetLevelVisibility(const TSoftObjectPtr<UWorld> Level, const bool bVisible, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		const auto HandleFinish = FOnHandleLevelStreamingOnceFinish::CreateLambda([&OnFinish]()
			{
				OnFinish.ExecuteIfBound();
			}
		);

		LevelStreamingManager->SetLevelVisibility(Level, bVisible, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::SetLevelsVisibility(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->SetLevelsVisibility(Levels, bVisible, HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::LoadCurrentWorldLevelStreaming(FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->LoadCurrentWorldLevelStreaming(HandleOnceFinish, HandleFinish);
	}
}

void UBPFunctions_LevelStreaming::UnLoadCurrentWorldLevelStreaming(FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish)
{
	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
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

		LevelStreamingManager->UnLoadCurrentWorldLevelStreaming(HandleOnceFinish, HandleFinish);
	}
}

ULevelStreaming* UBPFunctions_LevelStreaming::GetLevelStreaming(TSoftObjectPtr<UWorld> Level)
{
	if (const ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		return LevelStreamingManager->GetLevelStreaming(Level);
	}
	return nullptr;
}

bool UBPFunctions_LevelStreaming::IsLevelLoaded(TSoftObjectPtr<UWorld> Level)
{
	if (const ULevelStreaming* LevelStreaming = GetLevelStreaming(Level))
	{
		return LevelStreaming->IsLevelLoaded();
	}
	return false;
}

bool UBPFunctions_LevelStreaming::IsCurrentWorldContainLevel(TSoftObjectPtr<UWorld> Level, bool& Contain)
{
	if (const ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		Contain = LevelStreamingManager->IsCurrentWorldContainLevel(Level);
		return true;
	}
	return false;
}
