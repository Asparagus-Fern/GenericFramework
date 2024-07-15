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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"), Category="OnActived")
	FGameplayTag ActiveSwitchCameraTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="OnActived")
	UCameraHandle* ActiveSwitchCameraHandle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"), Category="OnInactived")
	FGameplayTag InactiveSwitchCameraTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="OnInactived")
	UCameraHandle* InactiveSwitchCameraHandle = nullptr;

protected:
	FDelegateHandle SwitchCameraFinishHandle;
	void OnActiveSwitchCameraFinish(UCameraHandle* InCameraHandle);
	void OnInactiveSwitchCameraFinish(UCameraHandle* InCameraHandle);
};
