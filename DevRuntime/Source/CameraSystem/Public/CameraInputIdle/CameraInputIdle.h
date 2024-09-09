// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Input/InputIdle.h"
#include "CameraInputIdle.generated.h"

class UCameraLensMovement;
class UCameraHandle;

/**
 * 相机空闲状态的数据
 */
UCLASS()
class CAMERASYSTEM_API UCameraInputIdle : public UInputIdle
{
	GENERATED_BODY()

	/* CameraAutoSwitch */
public:
	/* 是否启用自动相机切换 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Auto Switch")
	bool bEnableCameraAutoSwitch = true;

	/* 是否重置切换的下标，如果为true，每次开始自动切换都将从下标0开始，如果为false */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableCameraAutoSwitch"), Category="Camera Auto Switch")
	bool bResetAutoSwitchIndex = true;

	/* 间隔时间是否包含切换的时间 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableCameraAutoSwitch"), Category="Camera Auto Switch")
	bool bIsTimerContainerHandleDuration = true;

	/* 切换的时间间隔 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableCameraAutoSwitch"), Category="Camera Auto Switch")
	float TimeInterval = 5.f;

	/* 切换的处理 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(EditCondition = "bEnableCameraAutoSwitch"), Category="Camera Auto Switch")
	UCameraHandle* CameraHandle = nullptr;

	/* 自动切换的相机标签 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera", EditCondition = "bEnableCameraAutoSwitch"), Category="Camera Auto Switch")
	TArray<FGameplayTag> AutoSwitchTags;

public:
	/* 是否启用相机运镜 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Lens Movement")
	bool bEnableLensMovement = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta=(Categories="Camera", EditCondition = "bEnableLensMovement"), Category="Camera Lens Movement")
	TArray<UCameraLensMovement*> LensMovementList;
};
