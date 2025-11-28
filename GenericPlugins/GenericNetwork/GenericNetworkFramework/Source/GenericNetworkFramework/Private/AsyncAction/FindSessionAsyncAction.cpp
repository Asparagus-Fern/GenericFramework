// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "AsyncAction/FindSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "AsyncAction/CreateSessionAsyncAction.h"

UFindSessionAsyncAction::UFindSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete))
{
}

void UFindSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		SessionSearchSettings.EncodeSessionSearchSettings();
		if (!GenericSessionSubsystem->FindSessions(UniqueNetID, SessionSearchSettings, OnFindSessionsCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;
	}
	OnFail.Broadcast();
}

UFindSessionAsyncAction* UFindSessionAsyncAction::FindSessions(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, const FGenericSessionSearchSettings& InSessionSearchSettings)
{
	UFindSessionAsyncAction* NewAction = NewObject<UFindSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->SessionSearchSettings = InSessionSearchSettings;
	return NewAction;
}

void UFindSessionAsyncAction::OnFindSessionsComplete(bool bWasSuccessful)
{
	const TSharedRef<FOnlineSessionSearch> Search = SessionSearchSettings.GetSessionSearchSettings();

	if (Search->SearchState == EOnlineAsyncTaskState::Done || Search->SearchState == EOnlineAsyncTaskState::Failed)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		}

		SessionSearchSettings.DecodeSessionSearchSettings();

		SessionSearchResults.Reset();
		for (auto& Result : SessionSearchSettings.GetSessionSearchSettings()->SearchResults)
		{
			SessionSearchResults.Add(Result);
		}

		if (bWasSuccessful)
		{
			OnSuccess.Broadcast(SessionSearchResults);
		}
		else
		{
			OnFail.Broadcast();
		}
	}
}
