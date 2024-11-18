// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Manager/ManagerSetting.h"
#include "ManagerEdSetting.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEVEDCORE_API UManagerEdSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override;
};
