// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameMode/GenericGameMode.h"
#include "NetworkGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKAPPLICATION_API ANetworkGameMode : public AGenericGameMode
{
	GENERATED_UCLASS_BODY()

public:
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
