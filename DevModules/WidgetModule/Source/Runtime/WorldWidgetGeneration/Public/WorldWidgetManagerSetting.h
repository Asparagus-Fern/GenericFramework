// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "WorldWidgetManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UWorldWidgetManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
