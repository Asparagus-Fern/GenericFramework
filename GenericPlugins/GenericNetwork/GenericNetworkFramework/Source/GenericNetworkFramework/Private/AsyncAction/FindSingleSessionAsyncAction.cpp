// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/FindSingleSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

UFindSingleSessionAsyncAction::UFindSingleSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnSingleSessionResultCompleteDelegate(FOnSingleSessionResultCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete))
{
}

void UFindSingleSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (!GenericSessionSubsystem->FindSingleSession(PlayerUniqueNetID, SessionPlayerUniqueNetID, OnSingleSessionResultCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;
	}
	OnFail.Broadcast();
}

UFindSingleSessionAsyncAction* UFindSingleSessionAsyncAction::FindSingleSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerUniqueNetID, const FUniqueNetworkID& InSessionPlayerUniqueNetID)
{
	UFindSingleSessionAsyncAction* NewAction = NewObject<UFindSingleSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->PlayerUniqueNetID = InPlayerUniqueNetID;
	NewAction->SessionPlayerUniqueNetID = InSessionPlayerUniqueNetID;
	return NewAction;
}

void UFindSingleSessionAsyncAction::OnFindSessionComplete(int32 InPlayerIndex, bool bWasSuccessful, const FOnlineSessionSearchResult& InResult)
{
	if (bWasSuccessful)
	{
		OnSuccess.Broadcast(InResult);
	}
	else
	{
		OnFail.Broadcast();
	}
}
