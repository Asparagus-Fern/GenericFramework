// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "AsyncAction/CreateSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "ViewModel/SessionSettingViewModel.h"

void UCreateSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (ViewModelClass)
		{
			GenericSessionSubsystem->CreateSession(UniqueNetID, SessionName, ViewModelClass, FOnCreateSessionCompleteDelegate::CreateUObject(this, &UCreateSessionAsyncAction::OnCreateSessionComplete));
		}
		else if (ViewModel)
		{
			GenericSessionSubsystem->CreateSession(UniqueNetID, SessionName, ViewModel, FOnCreateSessionCompleteDelegate::CreateUObject(this, &UCreateSessionAsyncAction::OnCreateSessionComplete));
		}
	}
}

UCreateSessionAsyncAction* UCreateSessionAsyncAction::CreateSessionByClass(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, FName InSessionName, TSubclassOf<USessionSettingViewModel> InViewModelClass, bool IsAutoStart)
{
	UCreateSessionAsyncAction* NewAction = NewObject<UCreateSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->SessionName = InSessionName;
	NewAction->ViewModelClass = InViewModelClass;
	NewAction->bIsAutoStart = IsAutoStart;
	return NewAction;
}

UCreateSessionAsyncAction* UCreateSessionAsyncAction::CreateSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, FName InSessionName, USessionSettingViewModel* InViewModel, bool IsAutoStart)
{
	UCreateSessionAsyncAction* NewAction = NewObject<UCreateSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->SessionName = InSessionName;
	NewAction->ViewModel = InViewModel;
	NewAction->bIsAutoStart = IsAutoStart;
	return NewAction;
}

void UCreateSessionAsyncAction::OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
	{
		OnlineSessionPtr->ClearOnCreateSessionCompleteDelegates(this);
	}

	if (SessionName == InSessionName)
	{
		if (bIsAutoStart)
		{
			if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
			{
				GenericSessionSubsystem->StartSession(InSessionName, FOnStartSessionCompleteDelegate::CreateUObject(this, &UCreateSessionAsyncAction::OnStartSessionComplete));
			}
		}
		else
		{
			if (bWasSuccessful)
			{
				OnSuccess.Broadcast(ViewModel);
			}
			else
			{
				OnFail.Broadcast();
			}
		}
	}
}

void UCreateSessionAsyncAction::OnStartSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
	{
		OnlineSessionPtr->ClearOnStartSessionCompleteDelegates(this);
	}

	if (SessionName == InSessionName)
	{
		if (bWasSuccessful)
		{
			OnSuccess.Broadcast(ViewModel);
		}
		else
		{
			OnFail.Broadcast();
		}
	}
}
