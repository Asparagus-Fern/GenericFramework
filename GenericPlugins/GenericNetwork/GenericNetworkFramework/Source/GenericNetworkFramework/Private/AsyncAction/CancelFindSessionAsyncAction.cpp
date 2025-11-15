// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/CancelFindSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

void UCancelFindSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		GenericSessionSubsystem->CancelFindSessions(FOnCancelFindSessionsCompleteDelegate::CreateUObject(this, &UCancelFindSessionAsyncAction::OnCancelFindSessionsComplete));
	}
}

UCancelFindSessionAsyncAction* UCancelFindSessionAsyncAction::CancelFindSession(UObject* InWorldContextObject)
{
	UCancelFindSessionAsyncAction* NewAction = NewObject<UCancelFindSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	return NewAction;
}

void UCancelFindSessionAsyncAction::OnCancelFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFail.Broadcast();
	}
}
