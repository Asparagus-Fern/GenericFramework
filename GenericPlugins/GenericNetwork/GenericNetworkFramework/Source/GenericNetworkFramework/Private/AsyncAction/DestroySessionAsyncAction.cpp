// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/DestroySessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

UDestroySessionAsyncAction::UDestroySessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete))
{
}

void UDestroySessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (!GenericSessionSubsystem->DestroySession(SessionName, OnDestroySessionCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;;
	}
	OnFail.Broadcast();
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
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnDestroySessionRequestedDelegates(this);
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
}
