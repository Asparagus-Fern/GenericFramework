// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/JoinSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "BPFunctions/BPFunctions_Gameplay.h"

UJoinSessionAsyncAction::UJoinSessionAsyncAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete))
{
}

void UJoinSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (!GenericSessionSubsystem->JoinSession(UniqueNetID,SessionSearchResult, OnJoinSessionCompleteDelegate))
		{
			OnComplete.Broadcast(EJoinSessionResult::UnknownError);
		}
		return;
	}

	OnComplete.Broadcast(EJoinSessionResult::UnknownError);
}

UJoinSessionAsyncAction* UJoinSessionAsyncAction::JoinSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, const FGenericSessionSearchResult& InSessionSearchResult)
{
	UJoinSessionAsyncAction* NewAction = NewObject<UJoinSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->SessionSearchResult = InSessionSearchResult;
	return NewAction;
}

void UJoinSessionAsyncAction::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionSearchResult.GetSessionName() == InSessionName)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = GetOnlineSessionPtr())
		{
			OnlineSessionPtr->ClearOnJoinSessionCompleteDelegates(this);

			if (Result == EOnJoinSessionCompleteResult::Success) 
			{
				if (APlayerController* Player = UBPFunctions_Gameplay::GetPlayerControllerByUniqueNetID(WorldContextObject, APlayerController::StaticClass(), UniqueNetID.UniqueNetIdRepl))
				{
					FString ConnectString;
					if (OnlineSessionPtr->GetResolvedConnectString(InSessionName, ConnectString))
					{
						Player->ClientTravel(ConnectString, TRAVEL_Absolute);
					}
				}
			}
		}

		OnComplete.Broadcast(ConvertToJoinSessionResultBP(Result));
	}
}
