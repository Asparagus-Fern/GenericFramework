// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Handle/SetLevelStreamingVisibilityHandle.h"

#include "BPFunctions_LevelStreaming.h"
#include "LevelStreamingManager.h"
#include "Handle/UnLoadLevelStreamingHandle.h"
#include "Manager/ManagerStatics.h"

void USetLevelStreamingVisibilityHandle::Initialize(const FSetLevelStreamingVisibilitySetting& InSetting)
{
	Initialize(TArray<FSetLevelStreamingVisibilitySetting>{InSetting});
}

void USetLevelStreamingVisibilityHandle::Initialize(TArray<FSetLevelStreamingVisibilitySetting> InSettings)
{
	for (auto& Setting : InSettings)
	{
		if (Setting.IsValid() && !SetLevelStreamingVisibilitySettings.Contains(Setting))
		{
			SetLevelStreamingVisibilitySettings.Add(Setting);
		}
	}
}

void USetLevelStreamingVisibilityHandle::RemoveLevel(TSoftObjectPtr<UWorld> InLevel)
{
	const int32 Index = GetIndexByLevel(InLevel);
	if (Index > GetLevelIndex())
	{
		if (const FSetLevelStreamingVisibilitySetting* Found = SetLevelStreamingVisibilitySettings.FindByKey(InLevel))
		{
			SetLevelStreamingVisibilitySettings.Remove(*Found);
		}
	}
}

TArray<TSoftObjectPtr<UWorld>> USetLevelStreamingVisibilityHandle::GetLevels()
{
	TArray<TSoftObjectPtr<UWorld>> HandleLevels;

	for (auto& Setting : SetLevelStreamingVisibilitySettings)
	{
		HandleLevels.Add(Setting.Level);
	}

	return HandleLevels;
}

void USetLevelStreamingVisibilityHandle::ExecuteHandle(int32 Index)
{
	TArray<FLoadLevelStreamingSetting> LoadLevelSettings;
	for (auto& Level : GetLevels())
	{
		if (!UBPFunctions_LevelStreaming::IsLevelLoaded(Level))
		{
			LoadLevelSettings.Add(FLoadLevelStreamingSetting(Level, false, false));
		}
	}

	if (!LoadLevelSettings.IsEmpty())
	{
		GetManager<ULevelStreamingManager>()->LoadLevelsBySetting(LoadLevelSettings, nullptr, FOnHandleLevelStreamingFinish::CreateUObject(this, &USetLevelStreamingVisibilityHandle::LoadLevelsBeforeSetVisibility));
		return;
	}

	SetLevelVisibility(SetLevelStreamingVisibilitySettings[Index].Level, SetLevelStreamingVisibilitySettings[Index].bVisible);
}


void USetLevelStreamingVisibilityHandle::LoadLevelsBeforeSetVisibility()
{
	SetLevelVisibility(SetLevelStreamingVisibilitySettings[GetLevelIndex()].Level, SetLevelStreamingVisibilitySettings[GetLevelIndex()].bVisible);
}

void USetLevelStreamingVisibilityHandle::SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, const bool bVisible)
{
	if (ULevelStreaming* LevelStreaming = UBPFunctions_LevelStreaming::GetLevelStreaming(Level))
	{
		if (LevelStreaming->ShouldBeVisible() != bVisible)
		{
			LevelStreaming->OnLevelShown.AddDynamic(this, &USetLevelStreamingVisibilityHandle::OnLevelVisibilityChanged);
			LevelStreaming->OnLevelHidden.AddUniqueDynamic(this, &USetLevelStreamingVisibilityHandle::OnLevelVisibilityChanged);

			LevelStreaming->SetShouldBeVisible(bVisible);
			return;
		}
	}

	OnOnceFinish();
}

void USetLevelStreamingVisibilityHandle::OnLevelVisibilityChanged()
{
	if (ULevelStreaming* LevelStreaming = UBPFunctions_LevelStreaming::GetLevelStreaming(SetLevelStreamingVisibilitySettings[GetLevelIndex()].Level))
	{
		LevelStreaming->OnLevelShown.RemoveAll(this);
		LevelStreaming->OnLevelHidden.RemoveAll(this);
	}

	OnOnceFinish();
}
