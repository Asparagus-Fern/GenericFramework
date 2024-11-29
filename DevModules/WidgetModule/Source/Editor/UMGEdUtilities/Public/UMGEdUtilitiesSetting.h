// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerEdSetting.h"
#include "UMGEdUtilitiesSetting.generated.h"

/**
 * 
 */
UCLASS()
class UMGEDUTILITIES_API UUMGEdUtilitiesSetting : public UManagerEdSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(EditAnywhere, config, Category = "UMGSpline")
	float PanelHeight = 600.0f;
};
