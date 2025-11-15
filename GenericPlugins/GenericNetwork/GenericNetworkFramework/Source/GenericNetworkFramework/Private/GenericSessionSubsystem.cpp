// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericSessionSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Type/DebugType.h"
#include "ViewModel/SessionSearchSettingViewModel.h"
#include "ViewModel/SessionSettingViewModel.h"

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
}

void UGenericSessionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UGenericSessionSubsystem::CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, TSubclassOf<USessionSettingViewModel> InViewModelClass, const FOnCreateSessionCompleteDelegate& OnComplete)
{
	if (!InViewModelClass)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("ViewModelClass Is InValid"))
		return false;
	}

	return CreateSession(InUniqueNetID, InSessionName, NewObject<USessionSettingViewModel>(this, InViewModelClass), OnComplete);
}

bool UGenericSessionSubsystem::CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, USessionSettingViewModel* InViewModel, const FOnCreateSessionCompleteDelegate& OnComplete)
{
	if (!IsValid(InViewModel))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("ViewModel Is InValid"))
		return false;
	}

	SessionSettingViewModels.AddUnique(InViewModel);
	return CreateSession(InUniqueNetID, InSessionName, InViewModel->GetSessionSettings(), OnComplete);
}

bool UGenericSessionSubsystem::CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSettings& InSessionSettings, const FOnCreateSessionCompleteDelegate& OnComplete)
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

bool UGenericSessionSubsystem::FindSessions(const FUniqueNetworkID& InUniqueNetID, TSubclassOf<USessionSearchSettingViewModel> InViewModelClass, const FOnFindSessionsCompleteDelegate& OnComplete)
{
	if (!InViewModelClass)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("ViewModelClass Is InValid"))
		return false;
	}

	return FindSessions(InUniqueNetID, NewObject<USessionSearchSettingViewModel>(this, InViewModelClass), OnComplete);
}

bool UGenericSessionSubsystem::FindSessions(const FUniqueNetworkID& InUniqueNetID, USessionSearchSettingViewModel* InViewModel, const FOnFindSessionsCompleteDelegate& OnComplete)
{
	if (!IsValid(InViewModel))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("ViewModel Is InValid"))
		return false;
	}

	SessionSearchSettingViewModels.AddUnique(InViewModel);
	return FindSessions(InUniqueNetID, InViewModel->GetSessionSettings(), OnComplete);
}

bool UGenericSessionSubsystem::FindSessions(const FUniqueNetworkID& InUniqueNetID, const TSharedRef<FOnlineSessionSearch>& InSearchSettings, const FOnFindSessionsCompleteDelegate& OnComplete)
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
	if (!OnlineSessionPtr->FindSessions(InUniqueNetID.GetUniqueNetID(), InSearchSettings))
	{
		OnlineSessionPtr->ClearOnFindSessionsCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Find Sessions"))
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

	FDelegateHandle CompleteHandle;
	FOnCancelFindSessionsCompleteDelegate CompleteDelegate;
	CompleteDelegate.BindLambda([OnlineSessionPtr, &CompleteHandle, &OnComplete](bool bWasSuccessful)
		{
			OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegate_Handle(CompleteHandle);
			OnComplete.ExecuteIfBound(bWasSuccessful);
		}
	);

	CompleteHandle = OnlineSessionPtr->AddOnCancelFindSessionsCompleteDelegate_Handle(CompleteDelegate);
	if (!OnlineSessionPtr->CancelFindSessions())
	{
		OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegate_Handle(CompleteHandle);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Cancel Find Sessions"))
	return true;
}

bool UGenericSessionSubsystem::JoinSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSearchResult& DesiredSession, const FOnJoinSessionCompleteDelegate& OnComplete)
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

	FDelegateHandle CompleteHandle;
	FOnJoinSessionCompleteDelegate CompleteDelegate;
	CompleteDelegate.BindLambda([OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, EOnJoinSessionCompleteResult::Type Result)
		{
			OnlineSessionPtr->ClearOnJoinSessionCompleteDelegate_Handle(CompleteHandle);
			OnComplete.ExecuteIfBound(SessionName, Result);
		}
	);

	CompleteHandle = OnlineSessionPtr->AddOnJoinSessionCompleteDelegate_Handle(CompleteDelegate);
	if (!OnlineSessionPtr->JoinSession(InUniqueNetID.GetUniqueNetID(), InSessionName, DesiredSession))
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

	FDelegateHandle CompleteHandle;
	FOnEndSessionCompleteDelegate CompleteDelegate;
	CompleteDelegate.BindLambda([InSessionName, OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, bool bWasSuccessful)
		{
			if (InSessionName == SessionName)
			{
				OnlineSessionPtr->ClearOnEndSessionCompleteDelegate_Handle(CompleteHandle);
				OnComplete.ExecuteIfBound(InSessionName, bWasSuccessful);
			}
		}
	);

	CompleteHandle = OnlineSessionPtr->AddOnEndSessionCompleteDelegate_Handle(CompleteDelegate);
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

	FDelegateHandle CompleteHandle;
	FOnDestroySessionCompleteDelegate CompleteDelegate;
	CompleteDelegate.BindLambda([InSessionName, OnlineSessionPtr, &CompleteHandle, &OnComplete](FName SessionName, bool bWasSuccessful)
		{
			if (InSessionName == SessionName)
			{
				OnlineSessionPtr->ClearOnDestroySessionCompleteDelegate_Handle(CompleteHandle);
				OnComplete.ExecuteIfBound(InSessionName, bWasSuccessful);
			}
		}
	);

	CompleteHandle = OnlineSessionPtr->AddOnDestroySessionCompleteDelegate_Handle(CompleteDelegate);
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
