// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/StartSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

UStartSessionAsyncAction::UStartSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnStartCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
}

void UStartSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (!GenericSessionSubsystem->StartSession(SessionName, OnStartCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;
	}
	OnFail.Broadcast();
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
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnStartSessionCompleteDelegates(this);
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
