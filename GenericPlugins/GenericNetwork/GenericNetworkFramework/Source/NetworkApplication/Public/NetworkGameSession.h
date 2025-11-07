// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameSession/GenericGameSession.h"
#include "NetworkGameSession.generated.h"

class USessionSettingsViewModel;
class USessionCreateComponent;

UCLASS(Blueprintable)
class NETWORKAPPLICATION_API ANetworkGameSession : public AGenericGameSession
{
	GENERATED_BODY()

public:
	ANetworkGameSession();
// 	virtual void RegisterServer() override;
// 	virtual void RegisterServerFailed() override;
//
// protected:
// 	virtual UOnlineSessionCreateSettingsViewModel* GetOnlineSessionCreateSettingsViewModel();
//
// 	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
// 	TObjectPtr<USessionCreateComponent> SessionCreateComponent = nullptr;
};
