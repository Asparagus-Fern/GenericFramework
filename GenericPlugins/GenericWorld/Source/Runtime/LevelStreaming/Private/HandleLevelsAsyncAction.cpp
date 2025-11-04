// Copyright ChenTaiye 2025. All Rights Reserved.

#include "HandleLevelsAsyncAction.h"

#include "LevelStreamingSubsystem.h"


UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncLoadLevels(const UObject* WorldContextObject,const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->LoadLevels(Levels, bMakeVisibleAfterLoad, bShouldBlockOnLoad, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncLoadLevelsBySetting(const UObject* WorldContextObject,const TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->LoadLevelsBySetting(LoadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncUnloadLevels(const UObject* WorldContextObject,const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bShouldBlockOnUnload)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->UnloadLevels(Levels, bShouldBlockOnUnload, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncUnloadLevelsBySetting(const UObject* WorldContextObject,const TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->UnloadLevelsBySetting(UnloadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncSetLevelsVisibility(const UObject* WorldContextObject,const TArray<TSoftObjectPtr<UWorld>> Levels, const bool bVisible)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->SetLevelsVisibility(Levels, bVisible, FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncLoadCurrentWorldLevelStreaming(const UObject* WorldContextObject)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->LoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
	}

	return NewAction;
}

UHandleLevelsAsyncAction* UHandleLevelsAsyncAction::AsyncUnLoadCurrentWorldLevelStreaming(const UObject* WorldContextObject)
{
	UHandleLevelsAsyncAction* NewAction = NewObject<UHandleLevelsAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->UnLoadCurrentWorldLevelStreaming(FOnHandleLevelStreamingOnceFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish), FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelsAsyncAction::OnHandleOnceFinish));
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
