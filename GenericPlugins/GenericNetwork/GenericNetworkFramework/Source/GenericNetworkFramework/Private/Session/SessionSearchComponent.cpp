// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Session/SessionSearchComponent.h"

#include "GenericWidgetSubsystem.h"
#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Type/DebugType.h"
#include "ViewModel/SessionSearchSettingsViewModel.h"

USessionSearchComponent::USessionSearchComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void USessionSearchComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool USessionSearchComponent::FindSessionsByID(int32 HostingPlayerNum)
{
	FUniqueNetIdRepl UniqueNetID;
	if (UBPFunctions_Gameplay::GetPlayerUniqueNetIDByPlayerIndex(this, HostingPlayerNum, UniqueNetID))
	{
		FindSessionsByNetID(UniqueNetID);
	}

	return false;
}

bool USessionSearchComponent::FindSessionsByNetID(const FUniqueNetIdRepl& HostingPlayerId)
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
		OnlineSessionSearchSettings = NewObject<USessionSearchSettingsViewModel>(this, OnlineSessionSearchSettingsClass);
	}

	if (!OnlineSessionSearchSettings)
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("No Authority"))
		return false;
	}

	// if (!OnlineSessionSearchSettings->GetOnlineSessionSearchSettings(Settings))
	// {
	// 	GenericLOG(GenericLogNetwork, Error, TEXT("Fail To Get Online Session Settings"))
	// 	return false;
	// }

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

	GenericLOG(GenericLogNetwork, Display, TEXT("Find Sessions Start"))
	OnFindSessionStart.Broadcast();

	return true;
}

USessionSearchSettingsViewModel* USessionSearchComponent::GetOnlineSessionSearchSettings()
{
	return OnlineSessionSearchSettings;
}

void USessionSearchComponent::SetOnlineSessionSearchSettings(USessionSearchSettingsViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(OnlineSessionSearchSettings)

	OnlineSessionSearchSettings = InViewModel;

	if (OnlineSessionSearchSettings)
	{
	}
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
