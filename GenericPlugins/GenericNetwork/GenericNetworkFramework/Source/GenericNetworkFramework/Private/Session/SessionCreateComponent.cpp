// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Session/SessionCreateComponent.h"

#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Type/DebugType.h"
#include "ViewModel/SessionSettingsViewModel.h"

USessionCreateComponent::USessionCreateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USessionCreateComponent::CreateSessionByID(int32 InPlayerIndex, FName SessionName, USessionSettingsViewModel* InSettings)
{
	FUniqueNetIdRepl UniqueNetId;
	if (UBPFunctions_Gameplay::GetPlayerUniqueNetIDByPlayerIndex(this, InPlayerIndex, UniqueNetId))
	{
		return CreateSessionByNetID(UniqueNetId, SessionName, InSettings);
	}

	return false;
}

bool USessionCreateComponent::CreateSessionByNetID(const FUniqueNetIdRepl& InPlayerNetID, FName SessionName, USessionSettingsViewModel* InSettings)
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

	if (IsValid(InSettings))
	{
		OnlineSessionCreateSettings = InSettings;
	}
	else if (!IsValid(OnlineSessionCreateSettings))
	{
		if (OnlineSessionCreateSettingsClass)
		{
			OnlineSessionCreateSettings = NewObject<USessionSettingsViewModel>(this, OnlineSessionCreateSettingsClass);
		}
		else
		{
			OnlineSessionCreateSettings = NewObject<USessionSettingsViewModel>(this);
		}
	}

	FOnlineSessionSettings Settings;
	// if (!OnlineSessionCreateSettings->GetOnlineSessionCreateSettings(Settings))
	// {
	// 	GenericLOG(GenericLogNetwork, Display, TEXT("Fail To Get Online Session Settings"))
	// 	return false;
	// }

	FOnCreateSessionCompleteDelegate CreateDelegate;
	CreateDelegate.BindUObject(this, &USessionCreateComponent::OnCreateSessionComplete);
	OnlineSessionPtr->AddOnCreateSessionCompleteDelegate_Handle(CreateDelegate);

	if (!OnlineSessionPtr->CreateSession(*InPlayerNetID.GetUniqueNetId(), SessionName, Settings))
	{
		OnlineSessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		GenericLOG(GenericLogNetwork, Error, TEXT("Unable To Create Online Session"))
		return false;
	}

	GenericLOG(GenericLogNetwork, Display, TEXT("Create Online Session"))
	return true;
}

void USessionCreateComponent::OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (CreateSessionName == InSessionName)
	{
		if (IOnlineSessionPtr OnlineSessionPtr = Online::GetSessionInterface(GetWorld()))
		{
			OnlineSessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}

		if (bWasSuccessful)
		{
			GenericLOG(GenericLogNetwork, Display, TEXT("Create Online Session Success, Session Name : %s"), *InSessionName.ToString())
		}
		else
		{
			GenericLOG(GenericLogNetwork, Error, TEXT("Create Online Session Fail"))
		}

		OnSessionCreateCompleted.Broadcast(InSessionName, bWasSuccessful);
	}
}
