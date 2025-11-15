// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/EndSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

void UEndSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		GenericSessionSubsystem->EndSession(SessionName, FOnEndSessionCompleteDelegate::CreateUObject(this, &UEndSessionAsyncAction::OnEndSessionComplete));
	}
}

UEndSessionAsyncAction* UEndSessionAsyncAction::EndSession(UObject* InWorldContextObject, FName InSessionName)
{
	UEndSessionAsyncAction* NewAction = NewObject<UEndSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->SessionName = InSessionName;
	return NewAction;
}

void UEndSessionAsyncAction::OnEndSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (SessionName == InSessionName)
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
}
