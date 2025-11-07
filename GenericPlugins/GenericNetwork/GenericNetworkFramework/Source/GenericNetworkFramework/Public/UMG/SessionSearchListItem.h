// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Obect/GenericObject.h"
#include "Base/GenericWidget.h"
#include "SessionSearchListItem.generated.h"

class USessionSettingsViewModel;
class USessionSearchResultViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class USessionSearchListItemObject : public UGenericObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<USessionSearchResultViewModel> SessionSearchResultViewModel = nullptr;
};

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchListItem : public UGenericWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;
	virtual void NativeOnEntryReleased() override;

public:
	UFUNCTION(BlueprintPure)
	USessionSearchResultViewModel* GetSessionSearchResultViewModel();

	UFUNCTION(BlueprintCallable)
	void SetSessionSearchResultViewModel(USessionSearchResultViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnPingInMsChanged(int32 InPingInMs);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnUniqueIdReplChanged(FUniqueNetIdRepl InUniqueIdRepl);

	UFUNCTION(BlueprintNativeEvent)
	void OnOwningUserNameChanged(const FString& InOwningUserName);

	UFUNCTION(BlueprintNativeEvent)
	void OnSessionSettingsChanged(USessionSettingsViewModel* InSessionSettings);

	UFUNCTION(BlueprintNativeEvent)
	void OnNumOpenPrivateConnectionsChanged(int32 InNumOpenPrivateConnections);

	UFUNCTION(BlueprintNativeEvent)
	void OnNumOpenPublicConnectionsChanged(int32 InNumOpenPublicConnections);
	
	UPROPERTY()
	TObjectPtr<USessionSearchResultViewModel> SessionSearchResultViewModel = nullptr;

	UPROPERTY()
	TObjectPtr<USessionSettingsViewModel> SessionSettingsViewModel = nullptr;
};
