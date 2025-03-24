// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GlobalManagerSetting.generated.h"

/**
 * 
 */
UCLASS(config=ManagerSettings, DefaultConfig)
class DEVCORE_API UGlobalManagerSetting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FName GetContainerName() const override { return "Manager"; }
	virtual FName GetCategoryName() const override { return "Global"; }
	virtual FName GetSectionName() const override { return "Global"; }

public:
	UPROPERTY(Config, EditAnywhere, Category="Global Manager Setting")
	bool bEnableAllManager = true;
};
