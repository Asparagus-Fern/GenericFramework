// Copyright ChenTaiye 2025. All Rights Reserved.

#include "HandleLevelAsyncAction.h"

#include "LevelStreamingSubsystem.h"


UHandleLevelAsyncAction* UHandleLevelAsyncAction::LoadLevel(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	UHandleLevelAsyncAction* NewAction = NewObject<UHandleLevelAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->LoadLevel(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

UHandleLevelAsyncAction* UHandleLevelAsyncAction::UnloadLevel(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level, const bool bShouldBlockOnUnload)
{
	UHandleLevelAsyncAction* NewAction = NewObject<UHandleLevelAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->UnloadLevel(Level, bShouldBlockOnUnload, FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

UHandleLevelAsyncAction* UHandleLevelAsyncAction::SetLevelVisibility(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level, const bool bVisible)
{
	UHandleLevelAsyncAction* NewAction = NewObject<UHandleLevelAsyncAction>();

	if (ULevelStreamingSubsystem* LevelStreamingSubsystem = ULevelStreamingSubsystem::Get(WorldContextObject))
	{
		LevelStreamingSubsystem->SetLevelVisibility(Level, bVisible, FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void UHandleLevelAsyncAction::OnHandleFinish() const
{
	OnFinish.Broadcast();
}
