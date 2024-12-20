// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	bool bEnableAllManager = true;
};
