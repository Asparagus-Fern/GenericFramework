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
	virtual bool GetIsAsync() override { return true; }
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"))
	FGameplayTag ActiveSwitchCameraTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"))
	FGameplayTag InactiveSwitchCameraTag;

protected:
	FDelegateHandle SwitchCameraFinishHandle;
	void OnActiveSwitchCameraFinish(UCameraHandle* InCameraHandle);
	void OnInactiveSwitchCameraFinish(UCameraHandle* InCameraHandle);
};
