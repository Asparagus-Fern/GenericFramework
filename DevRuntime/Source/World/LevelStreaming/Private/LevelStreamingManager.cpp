// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamingManager.h"

#include "LevelStreamingManagerSetting.h"
#include "Debug/DebugType.h"
#include "Engine/LevelStreamingAlwaysLoaded.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "ULevelStreamingManager"

bool ULevelStreamingManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && ULevelStreamingManagerSetting::Get()->GetEnableManager() && !Cast<UWorld>(Outer)->IsPartitionedWorld();
}

void ULevelStreamingManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void ULevelStreamingManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool ULevelStreamingManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void ULevelStreamingManager::LoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Check */
	if (!CheckLevel(Level))
	{
		DLOG(DLogWorld, Warning, TEXT("InValid Level"))
		return;
	}

	const ULevelStreaming* LevelStreaming = GetLevelStreaming(Level);
	if (!IsValid(LevelStreaming))
	{
		DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
		return;
	}

	if (LevelStreaming->IsLevelLoaded())
	{
		OnFinish.ExecuteIfBound();
		DLOG(DLogWorld, Warning, TEXT("Level Is Already Load"));
		return;
	}

	ULoadLevelStreamingHandle* LoadLevelStreamingHandle = NewObject<ULoadLevelStreamingHandle>(this);
	const FLoadLevelStreamingSetting LoadLevelStreamingSetting(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad);
	LoadLevelStreamingHandle->HandleLoadLevel(LoadLevelStreamingSetting, OnFinish);
}

void ULevelStreamingManager::LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Make Sure Levels Is Not Empty */
	if (Levels.IsEmpty())
	{
		DLOG(DLogWorld, Warning, TEXT("Levels Is Empty"))
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Make FLoadLevelStreamingSetting */
	TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings;
	for (auto Level : Levels)
	{
		/* Check */
		if (!CheckLevel(Level))
		{
			DLOG(DLogWorld, Warning, TEXT("InValid Level"))
			continue;
		}

		const ULevelStreaming* LevelStreaming = GetLevelStreaming(Level);
		if (!IsValid(LevelStreaming))
		{
			DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
			continue;
		}

		/* 已经加载且可视性已经是指定可视性 */
		if (LevelStreaming->IsLevelLoaded() && LevelStreaming->ShouldBeVisible() == bMakeVisibleAfterLoad)
		{
			DLOG(DLogWorld, Warning, TEXT("Level Is Already Load"));
			continue;
		}

		if (Level.IsPending())
		{
			Level.LoadSynchronous();
		}
		LoadLevelStreamingSettings.Add(FLoadLevelStreamingSetting(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad));
	}

	if (LoadLevelStreamingSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Handle Valid Level */
	ULoadLevelStreamingHandle* LoadLevelStreamingHandle = NewObject<ULoadLevelStreamingHandle>(this);
	LoadLevelStreamingHandle->HandleLoadLevels(LoadLevelStreamingSettings, OnOnceFinish, OnFinish);
}

void ULevelStreamingManager::LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Make Sure Settings Is Not Empty */
	if (LoadLevelStreamingSettings.IsEmpty())
	{
		DLOG(DLogWorld, Warning, TEXT("Settings Is Empty"))
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Make FLoadLevelStreamingSetting */
	TArray<FLoadLevelStreamingSetting> CheckLoadLevelStreamingSettings;
	for (auto LoadLevelStreamingSetting : LoadLevelStreamingSettings)
	{
		if (LoadLevelStreamingSetting.Level.IsNull())
		{
			DLOG(DLogWorld, Warning, TEXT("InValid Level"))
		}
		else
		{
			CheckLoadLevelStreamingSettings.Add(LoadLevelStreamingSetting);
		}
	}

	if (CheckLoadLevelStreamingSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Handle Valid Level */
	ULoadLevelStreamingHandle* LoadLevelStreamingHandle = NewObject<ULoadLevelStreamingHandle>(this);
	LoadLevelStreamingHandle->HandleLoadLevels(CheckLoadLevelStreamingSettings, OnOnceFinish, OnFinish);
}

void ULevelStreamingManager::UnloadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bShouldBlockOnUnload, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Check */
	if (!CheckLevel(Level))
	{
		DLOG(DLogWorld, Warning, TEXT("InValid Level"))
		return;
	}

	const ULevelStreaming* LevelStreaming = GetLevelStreaming(Level);
	if (!IsValid(LevelStreaming))
	{
		DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
		return;
	}

	if (!LevelStreaming->IsLevelLoaded())
	{
		OnFinish.ExecuteIfBound();
		DLOG(DLogWorld, Warning, TEXT("Level Is Already Load"));
		return;
	}

	UUnloadLevelStreamingHandle* UnloadLevelStreamingHandle = NewObject<UUnloadLevelStreamingHandle>(this);
	const FUnloadLevelStreamingSetting UnloadLevelStreamingSetting(Level, bShouldBlockOnUnload);
	UnloadLevelStreamingHandle->HandleUnloadLevel(UnloadLevelStreamingSetting, OnFinish);
}

void ULevelStreamingManager::UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Make Sure Levels Is Not Empty */
	if (Levels.IsEmpty())
	{
		DLOG(DLogWorld, Warning, TEXT("Levels Is Empty"))
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Make FUnloadLevelStreamingSetting */
	TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings;
	for (auto Level : Levels)
	{
		/* Check */
		if (!CheckLevel(Level))
		{
			DLOG(DLogWorld, Warning, TEXT("InValid Level"))
			continue;
		}

		const ULevelStreaming* LevelStreaming = GetLevelStreaming(Level);
		if (!IsValid(LevelStreaming))
		{
			DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
			continue;
		}

		if (!LevelStreaming->IsLevelLoaded())
		{
			DLOG(DLogWorld, Warning, TEXT("Level Is Already Load"));
			continue;
		}

		UnloadLevelStreamingSettings.Add(FUnloadLevelStreamingSetting(Level, bShouldBlockOnUnload));
	}

	if (UnloadLevelStreamingSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Handle Valid Level */
	UUnloadLevelStreamingHandle* UnloadLevelStreamingHandle = NewObject<UUnloadLevelStreamingHandle>(this);
	UnloadLevelStreamingHandle->HandleUnloadLevels(UnloadLevelStreamingSettings, OnOnceFinish, OnFinish);
}

void ULevelStreamingManager::UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Make Sure Levels Is Not Empty */
	if (UnloadLevelStreamingSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Make FUnloadLevelStreamingSetting */
	TArray<FUnloadLevelStreamingSetting> CheckUnloadLevelStreamingSettings;
	for (auto UnloadLevelStreamingSetting : UnloadLevelStreamingSettings)
	{
		if (UnloadLevelStreamingSetting.Level.IsNull()) { DLOG(DLogWorld, Warning, TEXT("InValid Level")) }
		else { CheckUnloadLevelStreamingSettings.Add(UnloadLevelStreamingSetting); }
	}

	if (CheckUnloadLevelStreamingSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return;
	}

	/* Handle Valid Level */
	UUnloadLevelStreamingHandle* UnloadLevelStreamingHandle = NewObject<UUnloadLevelStreamingHandle>(this);
	UnloadLevelStreamingHandle->HandleUnloadLevels(CheckUnloadLevelStreamingSettings, OnOnceFinish, OnFinish);
}

void ULevelStreamingManager::SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, const bool bVisible, const FOnHandleLevelStreamingFinish& OnFinish)
{
	ULevelStreaming* LevelStreaming = GetLevelStreaming(Level);

	if (IsValid(LevelStreaming))
	{
		LevelStreaming->OnLevelShown.RemoveAll(this);
		LevelStreaming->OnLevelHidden.RemoveAll(this);

		/* 如果未加载 */
		if (!LevelStreaming->IsLevelLoaded())
		{
			LoadLevel(Level, bVisible, false, OnFinish);
			return;
		}

		/* 已经是指定的可视性 */
		if (bVisible == LevelStreaming->IsLevelVisible())
		{
			DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
			OnFinish.ExecuteIfBound();
			return;
		}

		ULevelStreamingVisibilityHandle* UnloadLevelStreamingHandle = NewObject<ULevelStreamingVisibilityHandle>(this);
		const FLevelStreamingVisibilitySetting UnloadLevelStreamingSetting(LevelStreaming, bVisible);
		UnloadLevelStreamingHandle->HandleSetLevelVisibility(UnloadLevelStreamingSetting, OnFinish);
	}
}

void ULevelStreamingManager::SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	if (Levels.IsEmpty())
	{
		DLOG(DLogWorld, Warning, TEXT("Levels Is Empty"))
		OnFinish.ExecuteIfBound();
		return;
	}

	/* 筛选有效的关卡 */
	TArray<TSoftObjectPtr<UWorld>> ValidLevels;
	for (auto& Level : Levels)
	{
		/* Check */
		if (!CheckLevel(Level))
		{
			DLOG(DLogWorld, Warning, TEXT("InValid Level"))
			continue;
		}

		const ULevelStreaming* LevelStreaming = GetLevelStreaming(Level);
		if (!IsValid(LevelStreaming))
		{
			DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
			continue;
		}

		/* 当前可视性为指定可视性时，跳过 */
		if (LevelStreaming->IsLevelVisible() == bVisible)
		{
			continue;
		}

		/* 设置可视性为隐藏，但关卡并未加载时，跳过*/
		if (!LevelStreaming->IsLevelLoaded() && !bVisible)
		{
			continue;
		}

		ValidLevels.Add(Level);
	}

	TArray<FLevelStreamingVisibilitySetting> LevelStreamingVisibilitySettings;
	for (const auto& Level : Levels)
	{
		LevelStreamingVisibilitySettings.Add(FLevelStreamingVisibilitySetting(GetLevelStreaming(Level), bVisible));
	}

	ULevelStreamingVisibilityHandle* LevelStreamingVisibilityHandle = NewObject<ULevelStreamingVisibilityHandle>(this);
	LevelStreamingVisibilityHandle->HandleSetLevelsVisibility(LevelStreamingVisibilitySettings, OnOnceFinish, OnFinish);
}

void ULevelStreamingManager::LoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* 获取需要加载的关卡 */
	TArray<TSoftObjectPtr<UWorld>> WorldToLoad;
	for (const auto StreamingLevel : GetWorld()->GetStreamingLevels())
	{
		/* 跳过已加载和以显示的关卡 */
		if (StreamingLevel->IsLevelVisible() || StreamingLevel->IsLevelLoaded())
		{
			continue;
		}

		/* 跳过非蓝图加载的关卡 */
		if (Cast<ULevelStreamingAlwaysLoaded>(StreamingLevel))
		{
			continue;
		}

		WorldToLoad.Add(StreamingLevel->GetWorldAsset());
	}

	if (!WorldToLoad.IsEmpty())
	{
		LoadLevels(WorldToLoad, false, false, OnOnceFinish, OnFinish);
	}
	else
	{
		OnFinish.ExecuteIfBound();
	}
}

void ULevelStreamingManager::UnLoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* 获取需要卸载的流关卡 */
	TArray<TSoftObjectPtr<UWorld>> WorldToUnLoad;
	for (const auto StreamingLevel : GetWorld()->GetStreamingLevels())
	{
		/* 跳过已卸载的关卡 */
		if (!StreamingLevel->IsLevelLoaded())
		{
			continue;
		}

		/* 跳过非蓝图加载的关卡 */
		if (Cast<ULevelStreamingAlwaysLoaded>(StreamingLevel))
		{
			continue;
		}

		WorldToUnLoad.Add(StreamingLevel->GetWorldAsset());
	}

	UnloadLevels(WorldToUnLoad, false, OnOnceFinish, OnFinish);
}

bool ULevelStreamingManager::IsCurrentWorldContainLevel(const TSoftObjectPtr<UWorld>& Level) const
{
	for (const auto StreamingLevel : GetWorld()->GetStreamingLevels())
	{
		FString PackageName;
		Level.GetLongPackageName().Split("/", &PackageName, nullptr, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		PackageName += ("/" + Level.GetAssetName());

		if (StreamingLevel->GetWorldAssetPackageFName() == PackageName || StreamingLevel->PackageNameToLoad == PackageName)
		{
			return true;
		}
	}
	return false;
}

bool ULevelStreamingManager::CheckLevel(const TSoftObjectPtr<UWorld>& Level) const
{
	if (Level.IsNull())
	{
		DLOG(DLogWorld, Warning, TEXT("InValid Level"))
		return false;
	}

	if (!IsCurrentWorldContainLevel(Level))
	{
		DLOG(DLogWorld, Warning, TEXT("Current World Not Contain Level : %s"), *Level.ToString());
		return false;
	}

	return true;
}

ULevelStreaming* ULevelStreamingManager::GetLevelStreaming(const TSoftObjectPtr<UWorld>& Level) const
{
	if (!CheckLevel(Level))
	{
		return nullptr;
	}

	const FString PackageName = FPackageName::ObjectPathToPackageName(Level.ToString());
	if (PackageName.IsEmpty())
	{
		DLOG(DLogWorld, Warning, TEXT("Level Is Not Found"))
		return nullptr;
	}

	ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, FName(*PackageName));
	if (!IsValid(LevelStreaming))
	{
		DLOG(DLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
		return nullptr;
	}

	return LevelStreaming;
}

#undef LOCTEXT
