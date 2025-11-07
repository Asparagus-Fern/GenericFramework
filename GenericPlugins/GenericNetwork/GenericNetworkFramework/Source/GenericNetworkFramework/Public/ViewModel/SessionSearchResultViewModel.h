// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineSessionSettings.h"
#include "SessionSearchResultViewModel.generated.h"

class USessionSettingsViewModel;

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchResultViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(const FOnlineSessionSearchResult& InResult);
	const FOnlineSessionSearchResult& GetSessionSearchResult() const { return Result; }

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetPingInMs() const;

	UFUNCTION(BlueprintCallable)
	void SetPingInMs(int32 InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	const FUniqueNetIdRepl& GetUniqueIdRepl() const;

	UFUNCTION(BlueprintCallable)
	void SetUniqueIdRepl(const FUniqueNetIdRepl& InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	FString GetOwningUserName() const;

	UFUNCTION(BlueprintCallable)
	void SetOwningUserName(FString InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	USessionSettingsViewModel* GetSessionSettings() const;

	UFUNCTION(BlueprintCallable)
	void SetSessionSettings(USessionSettingsViewModel* InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetNumOpenPrivateConnections() const;

	UFUNCTION(BlueprintCallable)
	void SetNumOpenPrivateConnections(int32 InValue);

	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetNumOpenPublicConnections() const;

	UFUNCTION(BlueprintCallable)
	void SetNumOpenPublicConnections(int32 InValue);

public:
	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetPingInMs", BlueprintSetter="SetPingInMs")
	int32 PingInMs;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetUniqueIdRepl", BlueprintSetter="SetUniqueIdRepl")
	FUniqueNetIdRepl UniqueIdRepl;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetOwningUserName", BlueprintSetter="SetOwningUserName")
	FString OwningUserName;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetSessionSettings", BlueprintSetter="SetSessionSettings")
	TObjectPtr<USessionSettingsViewModel> SessionSettings;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetNumOpenPrivateConnections", BlueprintSetter="SetNumOpenPrivateConnections")
	int32 NumOpenPrivateConnections;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetNumOpenPublicConnections", BlueprintSetter="SetNumOpenPublicConnections")
	int32 NumOpenPublicConnections;

private:
	FOnlineSessionSearchResult Result;
};
