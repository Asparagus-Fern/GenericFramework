// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "NetworkPlayerController.h"

#include "Session/SessionCreateComponent.h"
#include "Session/SessionSearchComponent.h"
#include "UniqueNetworkID/UniqueNetworkIDComponent.h"

ANetworkPlayerController::ANetworkPlayerController()
{
	UniqueNetworkIDComponent = CreateDefaultSubobject<UUniqueNetworkIDComponent>(TEXT("UniqueNetworkIDComponent"));
	SessionCreateComponent = CreateDefaultSubobject<USessionCreateComponent>(TEXT("SessionCreateComponent"));
	SessionSearchComponent = CreateDefaultSubobject<USessionSearchComponent>(TEXT("SessionSearchComponent"));
}
