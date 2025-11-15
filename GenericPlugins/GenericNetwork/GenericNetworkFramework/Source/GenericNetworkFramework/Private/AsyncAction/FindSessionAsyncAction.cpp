// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "AsyncAction/FindSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "AsyncAction/CreateSessionAsyncAction.h"
#include "ViewModel/SessionSearchSettingViewModel.h"

void UFindSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (ViewModelClass)
		{
			GenericSessionSubsystem->FindSessions(UniqueNetID, ViewModelClass, FOnFindSessionsCompleteDelegate::CreateUObject(this, &UFindSessionAsyncAction::OnFindSessionComplete));
		}
		else if (ViewModel)
		{
			GenericSessionSubsystem->FindSessions(UniqueNetID, ViewModel, FOnFindSessionsCompleteDelegate::CreateUObject(this, &UFindSessionAsyncAction::OnFindSessionComplete));
		}
	}
}

UFindSessionAsyncAction* UFindSessionAsyncAction::FindSessionsByClass(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, TSubclassOf<USessionSearchSettingViewModel> InViewModelClass)
{
	UFindSessionAsyncAction* NewAction = NewObject<UFindSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->ViewModelClass = InViewModelClass;
	return NewAction;
}

UFindSessionAsyncAction* UFindSessionAsyncAction::FindSessions(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, USessionSearchSettingViewModel* InViewModel)
{
	UFindSessionAsyncAction* NewAction = NewObject<UFindSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->ViewModel = InViewModel;
	return NewAction;
}

void UFindSessionAsyncAction::OnFindSessionComplete(bool bWasSuccessful)
{
	// TSharedRef<FOnlineSessionSearch> Search = ViewModel->GetSessionSettings();
	
	if (Search->SearchState == EOnlineAsyncTaskState::Done || Search->SearchState == EOnlineAsyncTaskState::Failed)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		}

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
