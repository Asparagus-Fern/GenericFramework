// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/CancelFindSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

UCancelFindSessionAsyncAction::UCancelFindSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnCancelFindSessionsCompleteDelegate(FOnCancelFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnCancelFindSessionsComplete))
{
}

void UCancelFindSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (!GenericSessionSubsystem->CancelFindSessions(OnCancelFindSessionsCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;
	}

	OnFail.Broadcast();
}

UCancelFindSessionAsyncAction* UCancelFindSessionAsyncAction::CancelFindSession(UObject* InWorldContextObject)
{
	UCancelFindSessionAsyncAction* NewAction = NewObject<UCancelFindSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	return NewAction;
}

void UCancelFindSessionAsyncAction::OnCancelFindSessionsComplete(bool bWasSuccessful)
{
	if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
	{
		OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegates(this);
	}

	if (bWasSuccessful)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFail.Broadcast();
	}
}
