#include "LevelStreamingType.h"

#include "Kismet/GameplayStatics.h"


void ULevelStreamingHandleBase::HandleLoadLevel(const FLoadLevelStreamingSetting& LoadLevelStreamingSetting, const FOnFinish InOnFinishDelegate)
{
	OnFinishDelegate = InOnFinishDelegate;
	Load(LoadLevelStreamingSetting.Level, LoadLevelStreamingSetting.bMakeVisibleAfterLoad, LoadLevelStreamingSetting.bShouldBlockOnLoad, "OnFinish", this);
}

void ULevelStreamingHandleBase::HandleLoadLevels(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, const FOnOnceFinish InOnOnceFinishDelegate, const FOnFinish InOnFinishDelegate)
{
	OnOnceFinishDelegate = InOnOnceFinishDelegate;
	OnFinishDelegate = InOnFinishDelegate;

	if (LoadLevelStreamingSettings.IsValidIndex(Index))
	{
		const FLoadLevelStreamingSetting LoadLevelStreamingSetting = LoadLevelStreamingSettings[Index];

		if (LoadLevelStreamingSetting.Level.IsNull())
		{
			OnOnceFinish();
		}
		else
		{
			Load(LoadLevelStreamingSetting.Level, LoadLevelStreamingSetting.bMakeVisibleAfterLoad, LoadLevelStreamingSetting.bShouldBlockOnLoad,TEXT("OnOnceFinish"), this);
		}
	}
}

void ULevelStreamingHandleBase::HandleUnloadLevel(const FUnloadLevelStreamingSetting& UnloadLevelStreamingSetting, const FOnFinish InOnFinishDelegate)
{
	OnFinishDelegate = InOnFinishDelegate;
	Unload(UnloadLevelStreamingSetting.Level, UnloadLevelStreamingSetting.bShouldBlockOnUnload, "OnFinish", this);
}

void ULevelStreamingHandleBase::HandleUnloadLevels(TArray<FUnloadLevelStreamingSetting> InUnloadLevelStreamingSettings, const FOnOnceFinish InOnOnceFinishDelegate, const FOnFinish InOnFinishDelegate)
{
	OnOnceFinishDelegate = InOnOnceFinishDelegate;
	OnFinishDelegate = InOnFinishDelegate;

	if (InUnloadLevelStreamingSettings.IsValidIndex(Index))
	{
		const FUnloadLevelStreamingSetting UnloadLevelStreamingSetting = InUnloadLevelStreamingSettings[Index];

		if (UnloadLevelStreamingSetting.Level.IsNull())
		{
			OnOnceFinish();
		}
		else
		{
			Unload(UnloadLevelStreamingSetting.Level, UnloadLevelStreamingSetting.bShouldBlockOnUnload,TEXT("OnOnceFinish"), this);
		}
	}
}

void ULevelStreamingHandleBase::HandleSetLevelVisibility(FLevelStreamingVisibilitySetting InLevelStreamingVisibilitySetting, FOnFinish InOnFinishDelegate)
{
	OnFinishDelegate = InOnFinishDelegate;
	SetLevelVisibility(InLevelStreamingVisibilitySetting.LevelStreaming, InLevelStreamingVisibilitySetting.bVisible);
}

void ULevelStreamingHandleBase::HandleSetLevelsVisibility(TArray<FLevelStreamingVisibilitySetting> InLevelStreamingVisibilitySettings, FOnOnceFinish InOnOnceFinishDelegate, FOnFinish InOnFinishDelegate)
{
	OnOnceFinishDelegate = InOnOnceFinishDelegate;
	OnFinishDelegate = InOnFinishDelegate;

	if (InLevelStreamingVisibilitySettings.IsValidIndex(Index))
	{
		const FLevelStreamingVisibilitySetting LevelStreamingVisibilitySetting = InLevelStreamingVisibilitySettings[Index];
		SetLevelVisibility(LevelStreamingVisibilitySetting.LevelStreaming, LevelStreamingVisibilitySetting.bVisible);
	}
}

void ULevelStreamingHandleBase::Load(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, const FString& CallbackName, UObject* CallbackObject) const
{
	const FLatentActionInfo LatentActionInfo(FMath::Rand(), FMath::Rand(), *CallbackName, CallbackObject);
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentActionInfo);
}

void ULevelStreamingHandleBase::Unload(const TSoftObjectPtr<UWorld>& Level, const bool bShouldBlockOnUnload, const FString& CallbackName, UObject* CallbackObject) const
{
	const FLatentActionInfo LatentActionInfo(FMath::Rand(), FMath::Rand(), *CallbackName, CallbackObject);
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, Level, LatentActionInfo, bShouldBlockOnUnload);
}

void ULevelStreamingHandleBase::SetLevelVisibility(ULevelStreaming* LevelStreaming, bool bVisible)
{
	if (!IsValid(LevelStreaming))
	{
		OnOnceFinish();
		return;
	}

	if (LevelStreaming->IsLevelVisible() == bVisible)
	{
		OnOnceFinish();
		return;
	}

	LevelStreaming->OnLevelShown.AddUniqueDynamic(this, &ULevelStreamingHandleBase::OnOnceFinish);
	LevelStreaming->OnLevelHidden.AddUniqueDynamic(this, &ULevelStreamingHandleBase::OnOnceFinish);

	LevelStreaming->SetShouldBeVisible(bVisible);
}

void ULoadLevelStreamingHandle::HandleLoadLevel(const FLoadLevelStreamingSetting& LoadLevelStreamingSetting, const FOnFinish InOnFinishDelegate)
{
	LoadLevelStreamingSettings = TArray<FLoadLevelStreamingSetting>{LoadLevelStreamingSetting};
	OnFinishDelegate = InOnFinishDelegate;
	Load(LoadLevelStreamingSetting.Level, LoadLevelStreamingSetting.bMakeVisibleAfterLoad, LoadLevelStreamingSetting.bShouldBlockOnLoad, "OnFinish", this);
}

void ULoadLevelStreamingHandle::HandleLoadLevels(const TArray<FLoadLevelStreamingSetting> InLoadLevelStreamingSettings, const FOnOnceFinish InOnOnceFinishDelegate, const FOnFinish InOnFinishDelegate)
{
	LoadLevelStreamingSettings = InLoadLevelStreamingSettings;
	Super::HandleLoadLevels(InLoadLevelStreamingSettings, InOnOnceFinishDelegate, InOnFinishDelegate);
}

void ULoadLevelStreamingHandle::OnOnceFinish()
{
	Super::OnOnceFinish();

	/* 进行下一个关卡流的加载 */
	Index++;
	if (LoadLevelStreamingSettings.IsValidIndex(Index))
	{
		const FLoadLevelStreamingSetting LoadLevelStreamingSetting = LoadLevelStreamingSettings[Index];
		Load(LoadLevelStreamingSetting.Level, LoadLevelStreamingSetting.bMakeVisibleAfterLoad, LoadLevelStreamingSetting.bShouldBlockOnLoad,TEXT("OnOnceFinish"), this);
	}
	else
	{
		/* 所有加载完成 */
		Index = 0;
		OnFinish();
	}
}

void UUnloadLevelStreamingHandle::HandleUnloadLevel(const FUnloadLevelStreamingSetting& UnloadLevelStreamingSetting, const FOnFinish InOnFinishDelegate)
{
	UnloadLevelStreamingSettings = TArray<FUnloadLevelStreamingSetting>{UnloadLevelStreamingSetting};
	Super::HandleUnloadLevel(UnloadLevelStreamingSetting, InOnFinishDelegate);
}

void UUnloadLevelStreamingHandle::HandleUnloadLevels(const TArray<FUnloadLevelStreamingSetting> InUnloadLevelStreamingSettings, const FOnOnceFinish InOnOnceFinishDelegate, const FOnFinish InOnFinishDelegate)
{
	UnloadLevelStreamingSettings = InUnloadLevelStreamingSettings;
	Super::HandleUnloadLevels(InUnloadLevelStreamingSettings, InOnOnceFinishDelegate, InOnFinishDelegate);
}

void UUnloadLevelStreamingHandle::OnOnceFinish()
{
	Super::OnOnceFinish();

	/* 进行下一个关卡流的加载 */
	Index++;
	if (UnloadLevelStreamingSettings.IsValidIndex(Index))
	{
		const FUnloadLevelStreamingSetting UnloadLevelStreamingSetting = UnloadLevelStreamingSettings[Index];
		Unload(UnloadLevelStreamingSetting.Level, UnloadLevelStreamingSetting.bShouldBlockOnUnload,TEXT("OnOnceFinish"), this);
	}
	else
	{
		/* 所有加载完成 */
		Index = 0;
		OnFinish();
	}
}

void ULevelStreamingVisibilityHandle::HandleSetLevelVisibility(FLevelStreamingVisibilitySetting InLevelStreamingVisibilitySetting, FOnFinish InOnFinishDelegate)
{
	LevelStreamingVisibilitySettings = TArray<FLevelStreamingVisibilitySetting>{InLevelStreamingVisibilitySetting};
	Super::HandleSetLevelVisibility(InLevelStreamingVisibilitySetting, InOnFinishDelegate);
}

void ULevelStreamingVisibilityHandle::HandleSetLevelsVisibility(TArray<FLevelStreamingVisibilitySetting> InLevelStreamingVisibilitySettings, FOnOnceFinish InOnOnceFinishDelegate, FOnFinish InOnFinishDelegate)
{
	LevelStreamingVisibilitySettings = InLevelStreamingVisibilitySettings;
	Super::HandleSetLevelsVisibility(InLevelStreamingVisibilitySettings, InOnOnceFinishDelegate, InOnFinishDelegate);
}

void ULevelStreamingVisibilityHandle::OnOnceFinish()
{
	Super::OnOnceFinish();

	/* 进行下一个关卡流的显隐 */
	Index++;
	if (LevelStreamingVisibilitySettings.IsValidIndex(Index))
	{
		const FLevelStreamingVisibilitySetting LevelStreamingVisibilitySetting = LevelStreamingVisibilitySettings[Index];
		SetLevelVisibility(LevelStreamingVisibilitySetting.LevelStreaming, LevelStreamingVisibilitySetting.bVisible);
	}
	else
	{
		/* 所有显隐完成 */
		Index = 0;
		OnFinish();
	}
}

void ULevelStreamingVisibilityHandle::OnFinish()
{
	/* 清理回调 */
	for (auto LevelStreamingVisibilitySetting : LevelStreamingVisibilitySettings)
	{
		if (IsValid(LevelStreamingVisibilitySetting.LevelStreaming))
		{
			LevelStreamingVisibilitySetting.LevelStreaming->OnLevelShown.RemoveAll(this);
			LevelStreamingVisibilitySetting.LevelStreaming->OnLevelHidden.RemoveAll(this);
		}
	}

	Super::OnFinish();
}

// FLevelsVisibilityHandle::FLevelsVisibilityHandle()
// 	: Levels(),
// 	  bVisible(false),
// 	  OnOnceFinish(),
// 	  OnFinish()
// {
// }
//
// FLevelsVisibilityHandle::FLevelsVisibilityHandle(TArray<TSoftObjectPtr<UWorld>> InLevels, bool InVisible, FOnOnceFinish InOnceFinish, FOnFinish InFinish)
// 	: Levels(InLevels),
// 	  bVisible(InVisible),
// 	  OnOnceFinish(InOnceFinish),
// 	  OnFinish(InFinish)
// {
// }
