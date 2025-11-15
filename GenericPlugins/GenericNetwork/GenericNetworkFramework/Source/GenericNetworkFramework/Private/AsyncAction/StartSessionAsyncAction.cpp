// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/StartSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

void UStartSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		GenericSessionSubsystem->StartSession(SessionName, FOnStartSessionCompleteDelegate::CreateUObject(this, &UStartSessionAsyncAction::OnStartSessionComplete));
	}
}

UStartSessionAsyncAction* UStartSessionAsyncAction::StartSession(UObject* InWorldContextObject, FName InSessionName)
{
	UStartSessionAsyncAction* NewAction = NewObject<UStartSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->SessionName = InSessionName;
	return NewAction;
}

void UStartSessionAsyncAction::OnStartSessionComplete(FName InSessionName, bool bWasSuccessful)
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
