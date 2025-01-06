// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputIdle.generated.h"

class UInputManager;

/**
 * 注册到InputManager，当没有任何输入时切换到空闲状态
 */
UCLASS(BlueprintType)
class DEVCORE_API UInputIdle : public UDataAsset
{
	GENERATED_BODY()

	friend UInputManager;

public:
	/* 空闲时间阈值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IdleTime = 5.f;
};
