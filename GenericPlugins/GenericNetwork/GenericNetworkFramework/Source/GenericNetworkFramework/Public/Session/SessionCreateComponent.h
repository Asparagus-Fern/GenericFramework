// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SessionCreateComponent.generated.h"

class USessionSettingsViewModel;
class FOnlineSessionSettings;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionCreateCompleted, FName, SessionName, bool, bWasSuccessful);

/**
 * 
 */
UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent), MinimalAPI)
class USessionCreateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USessionCreateComponent();

public:
	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool CreateSessionByID(int32 InPlayerIndex, FName SessionName, USessionSettingsViewModel* InSettings = nullptr);

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool CreateSessionByNetID(const FUniqueNetIdRepl& InPlayerNetID, FName SessionName, USessionSettingsViewModel* InSettings = nullptr);

	UPROPERTY(BlueprintAssignable)
	FOnSessionCreateCompleted OnSessionCreateCompleted;

protected:
	GENERICNETWORKFRAMEWORK_API virtual void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USessionSettingsViewModel> OnlineSessionCreateSettingsClass = nullptr;

	UPROPERTY()
	TObjectPtr<USessionSettingsViewModel> OnlineSessionCreateSettings = nullptr;

private:
	FName CreateSessionName = NAME_None;
};
