// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "SceneManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API USceneManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
