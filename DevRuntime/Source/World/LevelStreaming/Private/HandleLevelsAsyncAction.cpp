// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleLevelsAsyncAction.h"

#include "LevelStreamingManager.h"

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::LoadLevels(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevels(Levels, bMakeVisibleAfterLoad, bShouldBlockOnLoad, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::LoadLevelsBySetting(const TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevelsBySetting(LoadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::UnloadLevels(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->UnloadLevels(Levels, bShouldBlockOnUnload, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::UnloadLevelsBySetting(const TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->UnloadLevelsBySetting(UnloadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::SetLevelsVisibility(const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->SetLevelsVisibility(Levels, bVisible, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::LoadCurrentWorldLevelStreaming()
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::UnLoadCurrentWorldLevelStreaming()
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = GetManager<ULevelStreamingManager>())
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
