// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerEdSetting.h"
#include "WorldWidgetEdManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class WORLDWIDGETEDGENERATION_API UWorldWidgetEdManagerSetting : public UManagerEdSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
};
