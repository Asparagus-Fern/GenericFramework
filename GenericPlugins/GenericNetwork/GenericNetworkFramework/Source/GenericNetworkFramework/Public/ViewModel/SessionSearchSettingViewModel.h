// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "SessionSearchSettingViewModel.generated.h"

class USessionSearchResultViewModel;
/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchSettingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	TSharedRef<FOnlineSessionSearch> GetSessionSearchSettings() const;
	void SetSessionSearchSettings(const TSharedRef<FOnlineSessionSearch>& InSessionSettings);

public:
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadOnly)
	FGenericSessionSearchSettings SessionSearchSettings;
};
