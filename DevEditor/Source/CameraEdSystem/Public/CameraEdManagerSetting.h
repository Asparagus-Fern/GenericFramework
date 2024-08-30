// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerEdSetting.h"
#include "CameraEdManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class CAMERAEDSYSTEM_API UCameraEdManagerSetting : public UManagerEdSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
