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
	virtual FName GetCategoryName() const override;
};
