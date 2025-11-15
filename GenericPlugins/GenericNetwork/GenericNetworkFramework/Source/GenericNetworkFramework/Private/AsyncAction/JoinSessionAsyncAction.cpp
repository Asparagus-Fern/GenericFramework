// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/JoinSessionAsyncAction.h"

#include "GenericSessionSubsystem.h"
#include "ViewModel/SessionSearchResultViewModel.h"
#include "ViewModel/SessionSettingViewModel.h"

void UJoinSessionAsyncAction::Activate()
{
	Super::Activate();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(WorldContextObject))
	{
		if (ViewModel)
		{
			GenericSessionSubsystem->JoinSession(UniqueNetID, ViewModel->GetSessionName(), ViewModel->GetSessionSearchResult(), FOnJoinSessionCompleteDelegate::CreateUObject(this, &UJoinSessionAsyncAction::OnJoinSessionComplete));
		}
	}
}

UJoinSessionAsyncAction* UJoinSessionAsyncAction::JoinSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, USessionSearchResultViewModel* InViewModel)
{
	UJoinSessionAsyncAction* NewAction = NewObject<UJoinSessionAsyncAction>();
	NewAction->WorldContextObject = InWorldContextObject;
	NewAction->UniqueNetID = InPlayerNetID;
	NewAction->ViewModel = InViewModel;
	return NewAction;
}

void UJoinSessionAsyncAction::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (ViewModel->GetSessionName() == InSessionName)
	{
		OnComplete.Broadcast(ConvertToJoinSessionResultBP(Result));
	}
}
