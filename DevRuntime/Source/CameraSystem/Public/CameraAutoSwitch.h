// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Input/InputIdle.h"
#include "CameraAutoSwitch.generated.h"

class UCameraHandle;

/**
 * 空闲时自动切换相机
 */
UCLASS()
class CAMERASYSTEM_API UCameraAutoSwitch : public UInputIdle
{
	GENERATED_BODY()

public:
	/* 切换的时间间隔 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeInterval = 5.f;

	/* 切换的处理 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UCameraHandle* CameraHandle;

	/* 自动切换的相机标签 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera"))
	TArray<FGameplayTag> AutoSwitchTags;
};
