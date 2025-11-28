// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "SessionSettingViewModel.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSettingViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	const FOnlineSessionSettings& GetSessionSettings() const;
	void SetSessionSettings(const FOnlineSessionSettings& InSettings);

public:
	UPROPERTY(FieldNotify, EditDefaultsOnly, BlueprintReadWrite)
	FGenericSessionSettings SessionSettings;
};
