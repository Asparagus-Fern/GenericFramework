// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UltraDynamicSkySettings.generated.h"

/**
 * 
 */
UCLASS(Config=UtilitySettings, DefaultConfig)
class ULTRADYNAMICSKYUTILITIES_API UUltraDynamicSkySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;

	static UUltraDynamicSkySettings* Get() { return GetMutableDefault<UUltraDynamicSkySettings>(); }

public:
	UPROPERTY(Config, EditDefaultsOnly)
	TSoftClassPtr<AActor> UltraDynamicSkyClass;
};
