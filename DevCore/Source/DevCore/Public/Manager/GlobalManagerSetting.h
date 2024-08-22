// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerSetting.h"
#include "GlobalManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGlobalManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere)
	bool bEnableManagerSubsystem = true;
};
