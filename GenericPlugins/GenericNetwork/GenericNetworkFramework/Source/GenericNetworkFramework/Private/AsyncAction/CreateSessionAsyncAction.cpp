// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "AsyncAction/CreateSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"

UCreateSessionAsyncAction::UCreateSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
	  , OnStartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
}

void UCreateSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull))
		{
			SessionSettings.MapName = World->GetMapName();
		}

		SessionSettings.EncodeSessionSettings();
		if (!GenericSessionSubsystem->CreateSession(UniqueNetID, SessionSettings, OnCreateSessionCompleteDelegate))
		{
			OnFail.Broadcast();
		}
		return;
	}

	OnFail.Broadcast();
}

UCreateSessionAsyncAction* UCreateSessionAsyncAction::CreateSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, const FGenericSessionSettings& InSessionSettings)
{
	UCreateSessionAsyncAction* NewAction = NewObject<UCreateSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->SessionSettings = InSessionSettings;
	return NewAction;
}

void UCreateSessionAsyncAction::OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (SessionSettings.SessionName == InSessionName)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}

		if (SessionSettings.bIsAutoStart)
		{
			if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
			{
				GenericSessionSubsystem->StartSession(InSessionName, OnStartSessionCompleteDelegate);
			}
		}
		else
		{
			if (bWasSuccessful)
			{
				OnSuccess.Broadcast(SessionSettings);
			}
			else
			{
				OnFail.Broadcast();
			}
		}
	}
}

void UCreateSessionAsyncAction::OnStartSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
	{
		OnlineSessionPtr->ClearOnStartSessionCompleteDelegates(this);
	}

	if (SessionSettings.SessionName == InSessionName)
	{
		if (bWasSuccessful)
		{
			OnSuccess.Broadcast(SessionSettings);
		}
		else
		{
			OnFail.Broadcast();
		}
	}
}
