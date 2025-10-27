// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SessionCreateComponent.generated.h"

class UOnlineSessionCreateSettingsViewModel;
class FOnlineSessionSettings;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionCreateCompleted, FName, SessionName, bool, bWasSuccessful);

/**
 * 
 */
UCLASS(ClassGroup=(GenericFreamwork), meta=(BlueprintSpawnableComponent), MinimalAPI)
class USessionCreateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USessionCreateComponent();

public:
	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool CreateSessionByID(int32 HostingPlayerNum, FName SessionName, UOnlineSessionCreateSettingsViewModel* InSettings = nullptr);

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool CreateSessionByNetID(const FUniqueNetIdRepl& HostingPlayerId, FName SessionName, UOnlineSessionCreateSettingsViewModel* InSettings = nullptr);

	UPROPERTY(BlueprintAssignable)
	FOnSessionCreateCompleted OnSessionCreateCompleted;

protected:
	GENERICNETWORKFRAMEWORK_API virtual void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UOnlineSessionCreateSettingsViewModel> OnlineSessionCreateSettingsClass = nullptr;

	UPROPERTY()
	TObjectPtr<UOnlineSessionCreateSettingsViewModel> OnlineSessionCreateSettings = nullptr;

private:
	FName CreateSessionName = NAME_None;
};
