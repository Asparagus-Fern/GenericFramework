// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/GenericPlayerController.h"
#include "NetworkPlayerController.generated.h"

class UOnlineSessionCreateSettingsViewModel;
class USessionCreateComponent;
class USessionSearchComponent;
class UUniqueNetworkIDComponent;

/**
 * 
 */
UCLASS()
class NETWORKAPPLICATION_API ANetworkPlayerController : public AGenericPlayerController
{
	GENERATED_BODY()

public:
	ANetworkPlayerController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UUniqueNetworkIDComponent> UniqueNetworkIDComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USessionCreateComponent> SessionCreateComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USessionSearchComponent> SessionSearchComponent = nullptr;
};
