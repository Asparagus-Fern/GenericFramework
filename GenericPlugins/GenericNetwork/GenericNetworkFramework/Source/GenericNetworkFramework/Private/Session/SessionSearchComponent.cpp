// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Session/SessionSearchComponent.h"

#include "GenericWidgetManager.h"
#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Type/DebugType.h"
#include "UMG/SessionSearchPanel.h"
#include "ViewModel/OnlineSessionSearchSettingsViewModel.h"

USessionSearchComponent::USessionSearchComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void USessionSearchComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void USessionSearchComponent::OpenSessionSearchPanel()
{
	// if (SessionSearchPanelClass && !SessionSearchPanel)
	// {
	// 	if (APlayerController* Player = UBPFunctions_Gameplay::GetPlayerControllerByUniqueNetID(this, APlayerController::StaticClass(), HostingPlayerId))
	// 	{
	// 		SessionSearchPanel = CreateWidget<USessionSearchPanel>(Player, SessionSearchPanelClass);
	// 	}
	// }
	//
	// if (SessionSearchPanel)
	// {
	// 	FGenericWidgetHelper::OpenGenericWidget(SessionSearchPanel);
	// }
}

void USessionSearchComponent::CloseSessionSearchPanel()
{
	if (SessionSearchPanel)
	{
		FWidgetHelper::CloseGenericWidget(SessionSearchPanel);
	}
}

bool USessionSearchComponent::FindSessionsByID(int32 HostingPlayerNum, UOnlineSessionSearchSettingsViewModel* InSettings)
{
	FUniqueNetIdRepl UniqueNetID;
	if (UBPFunctions_Gameplay::GetPlayerUniqueNetIDByPlayerIndex(this, HostingPlayerNum, UniqueNetID))
	{
		FindSessionsByNetID(UniqueNetID, InSettings);
	}

	return false;
}

bool USessionSearchComponent::FindSessionsByNetID(const FUniqueNetIdRepl& HostingPlayerId, UOnlineSessionSearchSettingsViewModel* InSettings)
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
		GenericLOG(GenericLogNetwork, Error, TEXT("Online Session Is InValid"))
		return false;
	}

	if (GetOwnerRole() == ROLE_SimulatedProxy || GetOwnerRole() == ROLE_AutonomousProxy)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("No Authority"))
		return false;
	}


	if (OnlineSessionSearchSettingsClass && !OnlineSessionSearchSettings)
	{
		OnlineSessionSearchSettings = NewObject<UOnlineSessionSearchSettingsViewModel>(this, OnlineSessionSearchSettingsClass);
	}

	if (SessionSearchPanel && FWidgetHelper::OpenGenericWidget(SessionSearchPanel))
	{
		return false;
	}
	else
	{
		UOnlineSessionSearchSettingsViewModel* UseSettings = IsValid(InSettings) ? InSettings : OnlineSessionSearchSettings.Get();

		if (!UseSettings->GetOnlineSessionSearchSettings(Settings))
		{
			GenericLOG(GenericLogNetwork, Error, TEXT("Fail To Get Online Session Settings"))
			return false;
		}

		FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
		OnFindSessionsCompleteDelegate.BindUObject(this, &USessionSearchComponent::OnFindSessionsComplete);
		OnlineSessionPtr->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

		FOnCancelFindSessionsCompleteDelegate OnCancelFindSessionsCompleteDelegate;
		OnCancelFindSessionsCompleteDelegate.BindUObject(this, &USessionSearchComponent::OnCancelFindSessionsComplete);
		OnlineSessionPtr->AddOnCancelFindSessionsCompleteDelegate_Handle(OnCancelFindSessionsCompleteDelegate);

		if (!OnlineSessionPtr->FindSessions(*HostingPlayerId.GetUniqueNetId(), Settings.ToSharedRef()))
		{
			OnlineSessionPtr->ClearOnFindSessionsCompleteDelegates(this);
			OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegates(this);
			return false;
		}

		FindSessionsInternal();
		return true;
	}
}

void USessionSearchComponent::FindSessionsInternal()
{
	OnFindSessionStart.Broadcast();
	GenericLOG(GenericLogNetwork, Display, TEXT("Find Sessions Start"))
}

void USessionSearchComponent::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (Settings->SearchState == EOnlineAsyncTaskState::Done)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(GetWorld()))
		{
			OnlineSessionPtr->ClearOnFindSessionsCompleteDelegates(this);
			OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegates(this);
		}

		OnFindSessionSuccess.Broadcast();
		GenericLOG(GenericLogNetwork, Error, TEXT("Find Sessions Success"))
	}
	else if (Settings->SearchState == EOnlineAsyncTaskState::Failed)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(GetWorld()))
		{
			OnlineSessionPtr->ClearOnFindSessionsCompleteDelegates(this);
			OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegates(this);
		}

		OnFindSessionFail.Broadcast();
		GenericLOG(GenericLogNetwork, Error, TEXT("Find Sessions Fail"))
	}
}

void USessionSearchComponent::OnCancelFindSessionsComplete(bool bWasSuccessful)
{
	if (IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(GetWorld()))
	{
		OnlineSessionPtr->ClearOnFindSessionsCompleteDelegates(this);
		OnlineSessionPtr->ClearOnCancelFindSessionsCompleteDelegates(this);
	}

	if (bWasSuccessful)
	{
		OnFindSessionCancel.Broadcast();
		GenericLOG(GenericLogNetwork, Error, TEXT("Find Sessions Cancel"))
	}
	else
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Find Sessions Cancel Error"))
	}
}
