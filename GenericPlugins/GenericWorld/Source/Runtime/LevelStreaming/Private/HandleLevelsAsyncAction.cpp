// Copyright ChenTaiye 2025. All Rights Reserved.


#include "HandleLevelsAsyncAction.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerStatics.h"

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncLoadLevels(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevels(Levels, bMakeVisibleAfterLoad, bShouldBlockOnLoad, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncLoadLevelsBySetting(const TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevelsBySetting(LoadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncUnloadLevels(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->UnloadLevels(Levels, bShouldBlockOnUnload, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncUnloadLevelsBySetting(const TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->UnloadLevelsBySetting(UnloadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncSetLevelsVisibility(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->SetLevelsVisibility(Levels, bVisible, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncLoadCurrentWorldLevelStreaming()
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncUnLoadCurrentWorldLevelStreaming()
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManagerOwner<ULevelStreamingManager>())
	{
		LevelStreamingManager->UnLoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

void UHandleLevelsAsyncAction::OnHandleOnceFinish() const
{
	OnOnceFinish.Broadcast();
}

void UHandleLevelsAsyncAction::OnHandleFinish() const
{
	OnFinish.Broadcast();
}
