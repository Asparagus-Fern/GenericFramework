// Copyright ChenTaiye 2025. All Rights Reserved.


#include "LevelStreamingManager.h"

#include "BPFunctions_LevelStreaming.h"
#include "Debug/DebugType.h"
#include "Engine/LevelStreamingAlwaysLoaded.h"
#include "Handle/HandleManager.h"
#include "Handle/LoadLevelStreamingHandle.h"
#include "Handle/SetLevelStreamingVisibilityHandle.h"
#include "Handle/UnLoadLevelStreamingHandle.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerStatics.h"

#define LOCTEXT_NAMESPACE "FLevelStreamingModule"

bool ULevelStreamingManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !Cast<UWorld>(Outer)->IsPartitionedWorld();
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

ULoadLevelStreamingHandle* ULevelStreamingManager::LoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, const FOnHandleLevelStreamingFinish& OnFinish)
{
	const FLoadLevelStreamingSetting Setting = FLoadLevelStreamingSetting(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad);
	return LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting>{Setting}, nullptr, OnFinish);
}

ULoadLevelStreamingHandle* ULevelStreamingManager::LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	TArray<FLoadLevelStreamingSetting> Settings;

	for (auto& Level : Levels)
	{
		Settings.Add(FLoadLevelStreamingSetting(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad));
	}

	return LoadLevelsBySetting(Settings, OnOnceFinish, OnFinish);
}

ULoadLevelStreamingHandle* ULevelStreamingManager::LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Make Sure Settings Is Not Empty */
	if (InSettings.IsEmpty())
	{
		GenericLOG(GenericLogWorld, Warning, TEXT("Settings Is Empty"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	TArray<FLoadLevelStreamingSetting> ValidSettings;

	/* Loop To Get Valid Settings */
	for (auto Setting : InSettings)
	{
		if (!Setting.IsValid())
		{
			GenericLOG(GenericLogWorld, Warning, TEXT("Setting Is InValid"))
			continue;
		}

		if (!IsCurrentWorldContainLevel(Setting.Level))
		{
			GenericLOG(GenericLogWorld, Warning, TEXT("Current World Is Not Contain The Level : %s"), *Setting.Level->GetName())
			continue;
		}

		ValidSettings.Add(Setting);
	}

	CheckConflictLevelStreamHandle(ValidSettings);

	if (ValidSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	/* Handle Valid Level */
	if (UHandleManager* HandleManager = GetManagerOwner<UHandleManager>())
	{
		ULoadLevelStreamingHandle* LoadLevelStreamingHandle = HandleManager->RegisterHandle<ULoadLevelStreamingHandle>(this);
		LoadLevelStreamingHandle->GetHandleOnceFinishEvent().AddUObject(this, &ULevelStreamingManager::OnHandleLevelOnceFinish);
		LoadLevelStreamingHandle->GetHandleFinishEvent().AddUObject(this, &ULevelStreamingManager::OnHandleLevelFinish);
		LoadLevelStreamingHandle->Initialize(ValidSettings);

		LevelStreamingHandles.Add(LoadLevelStreamingHandle);

		LoadLevelStreamingHandle->Startup();
		return LoadLevelStreamingHandle;
	}

	return nullptr;
}

UUnLoadLevelStreamingHandle* ULevelStreamingManager::UnloadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bShouldBlockOnUnload, const FOnHandleLevelStreamingFinish& OnFinish)
{
	const FUnloadLevelStreamingSetting Setting = FUnloadLevelStreamingSetting(Level, bShouldBlockOnUnload);
	return UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting>{Setting}, nullptr, OnFinish);
}

UUnLoadLevelStreamingHandle* ULevelStreamingManager::UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	TArray<FUnloadLevelStreamingSetting> Settings;

	for (auto& Level : Levels)
	{
		Settings.Add(FUnloadLevelStreamingSetting(Level, bShouldBlockOnUnload));
	}

	return UnloadLevelsBySetting(Settings, OnOnceFinish, OnFinish);
}

UUnLoadLevelStreamingHandle* ULevelStreamingManager::UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	/* Make Sure Levels Is Not Empty */
	if (InSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	/* Loop To Get Valid Settings */
	TArray<FUnloadLevelStreamingSetting> ValidSettings;
	for (auto Setting : InSettings)
	{
		if (!Setting.IsValid())
		{
			GenericLOG(GenericLogWorld, Warning, TEXT("Setting Is InValid"))
			continue;
		}

		if (!IsCurrentWorldContainLevel(Setting.Level))
		{
			GenericLOG(GenericLogWorld, Warning, TEXT("Current World Is Not Contain The Level : %s"), *Setting.Level->GetName())
			continue;
		}

		ValidSettings.Add(Setting);
	}

	CheckConflictLevelStreamHandle(ValidSettings);

	if (ValidSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	/* Handle Valid Level */
	if (UHandleManager* HandleManager = GetManagerOwner<UHandleManager>())
	{
		UUnLoadLevelStreamingHandle* UnLoadLevelStreamingHandle = HandleManager->RegisterHandle<UUnLoadLevelStreamingHandle>(this);
		UnLoadLevelStreamingHandle->GetHandleOnceFinishEvent().AddUObject(this, &ULevelStreamingManager::OnHandleLevelOnceFinish);
		UnLoadLevelStreamingHandle->GetHandleFinishEvent().AddUObject(this, &ULevelStreamingManager::OnHandleLevelFinish);
		UnLoadLevelStreamingHandle->Initialize(ValidSettings);

		LevelStreamingHandles.Add(UnLoadLevelStreamingHandle);

		UnLoadLevelStreamingHandle->Startup();
		return UnLoadLevelStreamingHandle;
	}

	return nullptr;
}

USetLevelStreamingVisibilityHandle* ULevelStreamingManager::SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, const bool bVisible, const FOnHandleLevelStreamingFinish& OnFinish)
{
	const FSetLevelStreamingVisibilitySetting Setting = FSetLevelStreamingVisibilitySetting(Level, bVisible);
	return SetLevelsVisibilityBySetting(TArray<FSetLevelStreamingVisibilitySetting>{Setting}, nullptr, OnFinish);
}

USetLevelStreamingVisibilityHandle* ULevelStreamingManager::SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	TArray<FSetLevelStreamingVisibilitySetting> Settings;

	for (auto& Level : Levels)
	{
		Settings.Add(FSetLevelStreamingVisibilitySetting(Level, bVisible));
	}

	return SetLevelsVisibilityBySetting(Settings, OnOnceFinish, OnFinish);
}

USetLevelStreamingVisibilityHandle* ULevelStreamingManager::SetLevelsVisibilityBySetting(TArray<FSetLevelStreamingVisibilitySetting> InSettings, FOnHandleLevelStreamingOnceFinish OnOnceFinish, FOnHandleLevelStreamingFinish OnFinish)
{
	/* Make Sure Levels Is Not Empty */
	if (InSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	TArray<FSetLevelStreamingVisibilitySetting> ValidSettings;

	/* Loop To Get Valid Settings */
	for (auto Setting : InSettings)
	{
		if (!Setting.IsValid())
		{
			GenericLOG(GenericLogWorld, Warning, TEXT("Setting Is InValid"))
			continue;
		}

		if (!IsCurrentWorldContainLevel(Setting.Level))
		{
			GenericLOG(GenericLogWorld, Warning, TEXT("Current World Is Not Contain The Level : %s"), *Setting.Level->GetName())
			continue;
		}

		ValidSettings.Add(Setting);
	}

	CheckConflictLevelStreamHandle(ValidSettings);

	if (ValidSettings.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	/* Handle Valid Level */
	if (UHandleManager* HandleManager = GetManagerOwner<UHandleManager>())
	{
		USetLevelStreamingVisibilityHandle* SetLevelStreamingVisibilityHandle = HandleManager->RegisterHandle<USetLevelStreamingVisibilityHandle>(this);
		SetLevelStreamingVisibilityHandle->GetHandleOnceFinishEvent().AddUObject(this, &ULevelStreamingManager::OnHandleLevelOnceFinish);
		SetLevelStreamingVisibilityHandle->GetHandleFinishEvent().AddUObject(this, &ULevelStreamingManager::OnHandleLevelFinish);
		SetLevelStreamingVisibilityHandle->Initialize(ValidSettings);

		LevelStreamingHandles.Add(SetLevelStreamingVisibilityHandle);

		SetLevelStreamingVisibilityHandle->Startup();
		return SetLevelStreamingVisibilityHandle;
	}

	return nullptr;
}

ULoadLevelStreamingHandle* ULevelStreamingManager::LoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
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

	if (WorldToLoad.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return LoadLevels(WorldToLoad, false, false, OnOnceFinish, OnFinish);
}

UUnLoadLevelStreamingHandle* ULevelStreamingManager::UnLoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
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

	if (WorldToUnLoad.IsEmpty())
	{
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return UnloadLevels(WorldToUnLoad, false, OnOnceFinish, OnFinish);
}

ULevelStreaming* ULevelStreamingManager::GetLevelStreaming(TSoftObjectPtr<UWorld> Level) const
{
	if (Level.IsNull())
	{
		GenericLOG(GenericLogWorld, Warning, TEXT("Level Is InValid"))
		return nullptr;
	}

	const FString PackageName = FPackageName::ObjectPathToPackageName(Level.ToString());
	if (PackageName.IsEmpty())
	{
		GenericLOG(GenericLogWorld, Warning, TEXT("Level Package Is Not Found"))
		return nullptr;
	}

	ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, FName(*PackageName));
	if (!IsValid(LevelStreaming))
	{
		GenericLOG(GenericLogWorld, Warning, TEXT("Level Streaming Is Not Found"));
		return nullptr;
	}

	return LevelStreaming;
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

void ULevelStreamingManager::CheckConflictLevelStreamHandle(TArray<FLoadLevelStreamingSetting>& InSettings) const
{
	TSet<TSoftObjectPtr<UWorld>> SettingLevels;
	for (auto& InSetting : InSettings)
	{
		SettingLevels.Add(InSetting.Level);
	}

	TArray<TObjectPtr<ULevelStreamingHandle>> Handles = LevelStreamingHandles;
	for (auto& Handle : Handles)
	{
		if (UUnLoadLevelStreamingHandle* UnLoadLevelStreamingHandle = Cast<UUnLoadLevelStreamingHandle>(Handle))
		{
			TSet<TSoftObjectPtr<UWorld>> HandleLevels = TSet(UnLoadLevelStreamingHandle->GetLevels());

			for (const auto& ConflictLevel : SettingLevels.Intersect(HandleLevels).Array())
			{
				Handle->RemoveLevel(ConflictLevel);
			}
		}
	}
}

void ULevelStreamingManager::CheckConflictLevelStreamHandle(TArray<FUnloadLevelStreamingSetting>& InSettings) const
{
	TSet<TSoftObjectPtr<UWorld>> SettingLevels;
	for (auto& InSetting : InSettings)
	{
		SettingLevels.Add(InSetting.Level);
	}

	TArray<TObjectPtr<ULevelStreamingHandle>> Handles = LevelStreamingHandles;
	for (auto& Handle : Handles)
	{
		if (ULoadLevelStreamingHandle* LoadLevelStreamingHandle = Cast<ULoadLevelStreamingHandle>(Handle))
		{
			TSet<TSoftObjectPtr<UWorld>> HandleLevels = TSet(LoadLevelStreamingHandle->GetLevels());

			for (const auto& ConflictLevel : SettingLevels.Intersect(HandleLevels).Array())
			{
				Handle->RemoveLevel(ConflictLevel);
			}
		}
	}
}

void ULevelStreamingManager::CheckConflictLevelStreamHandle(TArray<FSetLevelStreamingVisibilitySetting>& InSettings) const
{
	TSet<TSoftObjectPtr<UWorld>> Visible;
	TSet<TSoftObjectPtr<UWorld>> Hidden;

	for (auto& InSetting : InSettings)
	{
		if (InSetting.bVisible)
		{
			Visible.Add(InSetting.Level);
		}
		else
		{
			Hidden.Add(InSetting.Level);
		}
	}

	TArray<TObjectPtr<ULevelStreamingHandle>> Handles = LevelStreamingHandles;
	for (auto& Handle : Handles)
	{
		if (ULoadLevelStreamingHandle* LoadLevelStreamingHandle = Cast<ULoadLevelStreamingHandle>(Handle))
		{
			TSet<TSoftObjectPtr<UWorld>> HandleLevels = TSet(LoadLevelStreamingHandle->GetLevels());

			for (const auto& ConflictLevel : Hidden.Intersect(HandleLevels).Array())
			{
				FLoadLevelStreamingSetting* LoadLevelStreamingSettingSetting = LoadLevelStreamingHandle->GetLoadLevelStreamingSettings().FindByKey(ConflictLevel);
				FSetLevelStreamingVisibilitySetting* SetLevelStreamingVisibilitySetting = InSettings.FindByKey(ConflictLevel);

				if (LoadLevelStreamingSettingSetting && SetLevelStreamingVisibilitySetting && LoadLevelStreamingSettingSetting->bMakeVisibleAfterLoad != SetLevelStreamingVisibilitySetting->bVisible)
				{
					Handle->RemoveLevel(ConflictLevel);
				}
			}
		}
		else if (UUnLoadLevelStreamingHandle* UnLoadLevelStreamingHandle = Cast<UUnLoadLevelStreamingHandle>(Handle))
		{
			TSet<TSoftObjectPtr<UWorld>> HandleLevels = TSet(UnLoadLevelStreamingHandle->GetLevels());

			for (const auto& ConflictLevel : Visible.Intersect(HandleLevels).Array())
			{
				Handle->RemoveLevel(ConflictLevel);
			}
		}
		else if (USetLevelStreamingVisibilityHandle* SetLevelStreamingVisibilityHandle = Cast<USetLevelStreamingVisibilityHandle>(Handle))
		{
			TSet<TSoftObjectPtr<UWorld>> HandleLevels = TSet(SetLevelStreamingVisibilityHandle->GetLevels());

			for (const auto& ConflictLevel : Visible.Intersect(HandleLevels).Array())
			{
				FSetLevelStreamingVisibilitySetting* HandleSetLevelStreamingVisibilitySetting = SetLevelStreamingVisibilityHandle->GetSetLevelStreamingVisibilitySettings().FindByKey(ConflictLevel);
				FSetLevelStreamingVisibilitySetting* SetLevelStreamingVisibilitySetting = InSettings.FindByKey(ConflictLevel);

				if (HandleSetLevelStreamingVisibilitySetting && SetLevelStreamingVisibilitySetting && HandleSetLevelStreamingVisibilitySetting->bVisible != SetLevelStreamingVisibilitySetting->bVisible)
				{
					Handle->RemoveLevel(ConflictLevel);
				}
			}
		}
	}
}

void ULevelStreamingManager::OnHandleLevelOnceFinish(ULevelStreamingHandle* InHandle, TSoftObjectPtr<UWorld> InLevel)
{
}

void ULevelStreamingManager::OnHandleLevelFinish(ULevelStreamingHandle* InHandle)
{
	InHandle->GetHandleOnceFinishEvent().RemoveAll(this);
	InHandle->GetHandleFinishEvent().RemoveAll(this);

	GetManagerOwner<UHandleManager>()->UnRegisterHandle(InHandle);
	LevelStreamingHandles.Remove(InHandle);
}

#undef LOCTEXT
