// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/DestroySessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

void UDestroySessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		GenericSessionSubsystem->DestroySession(SessionName, FOnDestroySessionCompleteDelegate::CreateUObject(this, &UDestroySessionAsyncAction::OnDestroySessionComplete));
	}
}

UDestroySessionAsyncAction* UDestroySessionAsyncAction::DestroySession(UObject* InWorldContextObject, FName InSessionName)
{
	UDestroySessionAsyncAction* NewAction = NewObject<UDestroySessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->SessionName = InSessionName;
	return NewAction;
}

void UDestroySessionAsyncAction::OnDestroySessionComplete(FName InSessionName, bool bWasSuccessful)
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
