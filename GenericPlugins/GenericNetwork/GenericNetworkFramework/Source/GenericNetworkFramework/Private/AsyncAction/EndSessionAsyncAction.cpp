// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/EndSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

UEndSessionAsyncAction::UEndSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnEndSessionCompleteDelegate(FOnEndSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnEndSessionComplete))
{
}

void UEndSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (!GenericSessionSubsystem->EndSession(SessionName, OnEndSessionCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;
	}
	OnFail.Broadcast();
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
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnEndSessionCompleteDelegates(this);
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
