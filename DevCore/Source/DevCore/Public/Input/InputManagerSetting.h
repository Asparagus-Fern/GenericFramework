// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputType.h"
#include "Manager/ManagerSetting.h"
#include "InputManagerSetting.generated.h"


/**
 * 
 */
UCLASS()
class DEVCORE_API UInputManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	/* 包含在此处的键位不会打断输入空闲的切换 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TArray<FKey> InputIdleNotInclude;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TArray<FEnhanceInputMappingContext> EnhanceInputMappingContexts;
};
