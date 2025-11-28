// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericSessionSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Type/DebugType.h"

UGenericSessionSubsystem* UGenericSessionSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance()->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UGenericSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete);
}

void UGenericSessionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UGenericSessionSubsystem::CreateSession(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSettings& InSessionSettings, const FOnCreateSessionCompleteDelegate& OnComplete)
{
	return CreateSession(InUniqueNetID, FName(InSessionSettings.SessionName), InSessionSettings.GetSessionSettings(), OnComplete);
}

bool UGenericSessionSubsystem::CreateSession(const FUniqueNetworkID& InUniqueNetID, const FName InSessionName, const FOnlineSessionSettings& InSessionSettings, const FOnCreateSessionCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	if (!OnlineSessionPtr->OnCreateSessionCompleteDelegates.IsBoundToObject(this))
	{
		OnlineSessionPtr->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
	}

	// FDelegateHandle CompleteHandle;
	// FOnCreateSessionCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([InSessionName, OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, bool bWasSuccessful)
	// 	{
	// 		if (InSessionName == SessionName)
	// 		{
	// 			OnlineSessionPtr->ClearOnCreateSessionCompleteDelegate_Handle(CompleteHandle);
	// 			OnComplete.ExecuteIfBound(InSessionName, bWasSuccessful);
	// 		}
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnCreateSessionCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->CreateSession(InUniqueNetID.GetUniqueNetID(), InSessionName, InSessionSettings))
	{
		OnlineSessionPtr->ClearOnCreateSessionCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Create Session"))
	SessionHandles.Emplace(FGenericSessionHandle(InUniqueNetID, InSessionName, InSessionSettings));
	return true;
}

bool UGenericSessionSubsystem::StartSession(FName InSessionName, const FOnStartSessionCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	// FDelegateHandle CompleteHandle;
	// FOnStartSessionCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([InSessionName, OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, bool bWasSuccessful)
	// 	{
	// 		if (InSessionName == SessionName)
	// 		{
	// 			OnlineSessionPtr->ClearOnStartSessionCompleteDelegate_Handle(CompleteHandle);
	// 			OnComplete.ExecuteIfBound(InSessionName, bWasSuccessful);
	// 		}
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnStartSessionCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->StartSession(InSessionName))
	{
		OnlineSessionPtr->ClearOnStartSessionCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Start Session"))
	return true;
}

bool UGenericSessionSubsystem::FindSessions(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSearchSettings& InSessionSearchSettings, const FOnFindSessionsCompleteDelegate& OnComplete)
{
	return FindSessions(InUniqueNetID, InSessionSearchSettings.GetSessionSearchSettings(), OnComplete);
}

bool UGenericSessionSubsystem::FindSessions(const FUniqueNetworkID& InUniqueNetID, const TSharedRef<FOnlineSessionSearch>& InSessionSearchSettings, const FOnFindSessionsCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	// FDelegateHandle CompleteHandle;
	// FOnFindSessionsCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([InSearchSettings, OnlineSessionPtr, &CompleteHandle, &OnComplete](bool bWasSuccessful)
	// 	{
	// 		if (InSearchSettings->SearchState == EOnlineAsyncTaskState::Done || InSearchSettings->SearchState == EOnlineAsyncTaskState::Failed)
	// 		{
	// 			OnlineSessionPtr->ClearOnFindSessionsCompleteDelegate_Handle(CompleteHandle);
	// 			OnComplete.ExecuteIfBound(bWasSuccessful);
	// 		}
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnFindSessionsCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->FindSessions(InUniqueNetID.GetUniqueNetID(), InSessionSearchSettings))
	{
		OnlineSessionPtr->ClearOnFindSessionsCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Find Sessions"))
	return true;
}

bool UGenericSessionSubsystem::FindSingleSession(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSearchResult& InResult, const FOnSingleSessionResultCompleteDelegate& OnComplete)
{
	return FindSingleSession(InUniqueNetID, InResult.OwnerPlayerID, OnComplete);
}

bool UGenericSessionSubsystem::FindSingleSession(const FUniqueNetworkID& InPlayerUniqueNetID, const FUniqueNetworkID& InSessionPlayerUniqueNetID, const FOnSingleSessionResultCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	if (!OnlineSessionPtr->FindSessionById(InPlayerUniqueNetID.GetUniqueNetID(), InSessionPlayerUniqueNetID.GetUniqueNetID(), *FUniqueNetIdString::EmptyId(), OnComplete))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Find Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Find Single Session"))
	return true;
}

bool UGenericSessionSubsystem::CancelFindSessions(const FOnCancelFindSessionsCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	// FDelegateHandle CompleteHandle;
	// FOnCancelFindSessionsCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([OnlineSessionPtr, &CompleteHandle, &OnComplete](bool bWasSuccessful)
	// 	{
	// 		OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegate_Handle(CompleteHandle);
	// 		OnComplete.ExecuteIfBound(bWasSuccessful);
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnCancelFindSessionsCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->CancelFindSessions())
	{
		OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Cancel Find Sessions"))
	return true;
}

bool UGenericSessionSubsystem::JoinSession(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSearchResult& InResult, const FOnJoinSessionCompleteDelegate& OnComplete)
{
	return JoinSession(InUniqueNetID, InResult.GetSessionName(), InResult.GetSessionSearchResult(), OnComplete);
}

bool UGenericSessionSubsystem::JoinSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FGenericSessionSearchResult& InResult, const FOnJoinSessionCompleteDelegate& OnComplete)
{
	return JoinSession(InUniqueNetID, InSessionName, InResult.GetSessionSearchResult(), OnComplete);
}

bool UGenericSessionSubsystem::JoinSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSearchResult& InResult, const FOnJoinSessionCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	// FDelegateHandle CompleteHandle;
	// FOnJoinSessionCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, EOnJoinSessionCompleteResult::Type Result)
	// 	{
	// 		OnlineSessionPtr->ClearOnJoinSessionCompleteDelegate_Handle(CompleteHandle);
	// 		OnComplete.ExecuteIfBound(SessionName, Result);
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnJoinSessionCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->JoinSession(InUniqueNetID.GetUniqueNetID(), InSessionName, InResult))
	{
		OnlineSessionPtr->ClearOnJoinSessionCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Join Session"))
	return true;
}

bool UGenericSessionSubsystem::EndSession(FName InSessionName, const FOnEndSessionCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	// FDelegateHandle CompleteHandle;
	// FOnEndSessionCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([InSessionName, OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, bool bWasSuccessful)
	// 	{
	// 		if (InSessionName == SessionName)
	// 		{
	// 			OnlineSessionPtr->ClearOnEndSessionCompleteDelegate_Handle(CompleteHandle);
	// 			OnComplete.ExecuteIfBound(InSessionName, bWasSuccessful);
	// 		}
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnEndSessionCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->EndSession(InSessionName))
	{
		OnlineSessionPtr->ClearOnEndSessionCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("End Session"))
	return true;
}

bool UGenericSessionSubsystem::DestroySession(FName InSessionName, const FOnDestroySessionCompleteDelegate& OnComplete)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	// FDelegateHandle CompleteHandle;
	// FOnDestroySessionCompleteDelegate CompleteDelegate;
	// CompleteDelegate.BindLambda([InSessionName, OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, bool bWasSuccessful)
	// 	{
	// 		if (InSessionName == SessionName)
	// 		{
	// 			OnlineSessionPtr->ClearOnDestroySessionCompleteDelegate_Handle(CompleteHandle);
	// 			OnComplete.ExecuteIfBound(InSessionName, bWasSuccessful);
	// 		}
	// 	}
	// );

	FDelegateHandle CompleteHandle = OnlineSessionPtr->AddOnDestroySessionCompleteDelegate_Handle(OnComplete);
	if (!OnlineSessionPtr->DestroySession(InSessionName))
	{
		OnlineSessionPtr->ClearOnDestroySessionCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Destroy Session"))
	return true;
}

bool UGenericSessionSubsystem::IsPlayerInSession(FName InSessionName, const FUniqueNetworkID& InUniqueNetID)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("World Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(World);
	if (!OnlineSessionPtr.IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Session Is InValid"))
		return false;
	}

	return OnlineSessionPtr->IsPlayerInSession(InSessionName, InUniqueNetID.GetUniqueNetID());
}

bool UGenericSessionSubsystem::GetSessionHandle(const FUniqueNetworkID& UniqueNetworkID, FGenericSessionHandle& OutHandle)
{
	return GetSessionHandle(UniqueNetworkID.UniqueNetIdRepl, OutHandle);
}

bool UGenericSessionSubsystem::GetSessionHandle(const FUniqueNetIdRepl& UniqueNetIDRepl, FGenericSessionHandle& OutHandle)
{
	for (auto& SessionHandle : SessionHandles)
	{
		if (SessionHandle.UniqueNetworkID.UniqueNetIdRepl == UniqueNetIDRepl)
		{
			OutHandle = SessionHandle;
			return true;
		}
	}
	return false;
}

bool UGenericSessionSubsystem::GetSessionHandle(const FName InSessionName, FGenericSessionHandle& OutHandle)
{
	for (auto& SessionHandle : SessionHandles)
	{
		if (SessionHandle.SessionName == InSessionName)
		{
			OutHandle = SessionHandle;
			return true;
		}
	}
	return false;
}

void UGenericSessionSubsystem::OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		for (auto SessionHandle : SessionHandles)
		{
			if (SessionHandle.SessionName == InSessionName)
			{
				SessionHandles.Remove(SessionHandle);
			}
		}
	}
}
