// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GameSettings.generated.h"

#define GET_GAME_SETTINGS_FUNCTION_PATH(FunctionName) \
	GET_PROPERTY_FUNCTION_PATH(PATH(UGameSettings, Get), PATH(UGameSettings, FunctionName))

/**
 * 测试
 */
UCLASS()
class APPLICATIONRUNTIME_API UGameSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UFUNCTION()
	static UGameSettings* Get();

public:
	UPROPERTY(Config)
	float Test2 = 0.f;

	UPROPERTY(Config)
	bool bTest3 = false;
};
