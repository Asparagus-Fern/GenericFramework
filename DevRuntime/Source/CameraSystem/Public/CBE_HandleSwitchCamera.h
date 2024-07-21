// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleSwitchCamera.generated.h"

class UCameraHandle;



/**
 * 处理相机的切换
 */
UCLASS()
class CAMERASYSTEM_API UCBE_HandleSwitchCamera : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UCBE_HandleSwitchCamera();
	virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 激活时需要切换的相机标签 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"), Category="OnActived")
	FGameplayTag ActiveSwitchCameraTag;

	/* 激活时切换相机的默认处理 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="OnActived")
	UCameraHandle* ActiveSwitchCameraHandle = nullptr;

	/* 不激活时需要切换的相机标签 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"), Category="OnInactived")
	FGameplayTag InactiveSwitchCameraTag;

	/* 不激活时切换相机的默认处理 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="OnInactived")
	UCameraHandle* InactiveSwitchCameraHandle = nullptr;

protected:
	FDelegateHandle SwitchCameraFinishHandle;
	void OnActiveSwitchCameraFinish(UCameraHandle* InCameraHandle);
	void OnInactiveSwitchCameraFinish(UCameraHandle* InCameraHandle);
};
