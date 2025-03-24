// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ManagerSetting.generated.h"

/**
 * 
 */
UCLASS(Abstract, config=ManagerSettings, DefaultConfig)
class DEVCORE_API UManagerSetting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;

public:
	UPROPERTY(Config, EditDefaultsOnly, Category="Manager Setting")
	int32 ManagerOrder = 0;

	UPROPERTY(Config, EditDefaultsOnly, Category="Manager Setting")
	FName ManagerName = NAME_None;
};
