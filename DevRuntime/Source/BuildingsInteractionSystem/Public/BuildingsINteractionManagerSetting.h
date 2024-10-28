// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "BuildingsINteractionManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UBuildingsINteractionManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
