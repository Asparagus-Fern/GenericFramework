// Fill out your copyright notice in the Description page of Project Settings.

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
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	bool bEnableSubsystem = true;
};
