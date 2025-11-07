// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "NetworkGameSession.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Session/SessionCreateComponent.h"
#include "ViewModel/SessionSettingsViewModel.h"

ANetworkGameSession::ANetworkGameSession()
{
	// SessionCreateComponent = CreateDefaultSubobject<USessionCreateComponent>(TEXT("SessionCreateComponent"));
}

/*void ANetworkGameSession::RegisterServer()
{
	Super::RegisterServer();

	UWorld* World = GetWorld();
	if (World && World->IsNetMode(NM_DedicatedServer))
	{
		SessionCreateComponent->CreateSessionByID(DEDICATED_SERVER_USER_INDEX, SessionName, GetOnlineSessionCreateSettingsViewModel());
	}
}

void ANetworkGameSession::RegisterServerFailed()
{
	Super::RegisterServerFailed();
}

UOnlineSessionCreateSettingsViewModel* ANetworkGameSession::GetOnlineSessionCreateSettingsViewModel()
{
	UOnlineSessionCreateSettingsViewModel* Settings = NewObject<UOnlineSessionCreateSettingsViewModel>(this);
	Settings->NumPublicConnections = MaxPlayers + MaxSpectators;
	Settings->NumPrivateConnections = MaxPlayers + MaxSpectators;
	Settings->bUseCustomGameModeDescription = true;
	Settings->GameModeDescriptionOverride = SessionName.ToString();
	return Settings;
}*/
