// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"

#include "SessionSearchPanel.generated.h"

class UOnlineSessionSearchSettingsViewModel;

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	UOnlineSessionSearchSettingsViewModel* GetSessionSearchSettingsViewModel();

	UFUNCTION(BlueprintCallable)
	void SetOnlineSessionSearchSettingsViewModel(UOnlineSessionSearchSettingsViewModel* InViewModel);

protected:
	UPROPERTY()
	TObjectPtr<UOnlineSessionSearchSettingsViewModel> OnlineSessionSearchSettingsViewModel = nullptr;

	// UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	// TObjectPtr<UGenericButtonWidget> Button_Apply;
};
