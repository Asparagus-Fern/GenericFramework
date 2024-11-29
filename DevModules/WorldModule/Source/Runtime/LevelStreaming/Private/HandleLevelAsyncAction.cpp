// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleLevelAsyncAction.h"

#include "LevelStreamingManager.h"
#include "Manager/ManagerProxy.h"

UHandleLevelAsyncAction* UHandleLevelAsyncAction::LoadLevel(const TSoftObjectPtr<UWorld> Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	UHandleLevelAsyncAction* NewAction = NewObject<UHandleLevelAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->LoadLevel(Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

UHandleLevelAsyncAction* UHandleLevelAsyncAction::UnloadLevel(const TSoftObjectPtr<UWorld> Level, const bool bShouldBlockOnUnload)
{
	UHandleLevelAsyncAction* NewAction = NewObject<UHandleLevelAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->UnloadLevel(Level, bShouldBlockOnUnload, FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

UHandleLevelAsyncAction* UHandleLevelAsyncAction::SetLevelVisibility(const TSoftObjectPtr<UWorld> Level, const bool bVisible)
{
	UHandleLevelAsyncAction* NewAction = NewObject<UHandleLevelAsyncAction>();

	if (ULevelStreamingManager* LevelStreamingManager = UManagerProxy::Get()->GetManager<ULevelStreamingManager>())
	{
		LevelStreamingManager->SetLevelVisibility(Level, bVisible, FOnHandleLevelStreamingFinish::CreateUObject(NewAction, &UHandleLevelAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void UHandleLevelAsyncAction::OnHandleFinish() const
{
	OnFinish.Broadcast();
}
