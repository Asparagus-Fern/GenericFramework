// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "CameraManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UCameraManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere)
	bool bDestroyEmptyCameraPointAfterSwitchFinish = true;
};
