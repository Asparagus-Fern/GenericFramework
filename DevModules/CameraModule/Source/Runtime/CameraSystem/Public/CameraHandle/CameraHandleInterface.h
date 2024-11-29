// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraHandleInterface.generated.h"

class UCameraHandle;

UINTERFACE()
class UCameraHandleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAMERASYSTEM_API ICameraHandleInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Camera Hadnle Interface")
	void HandleSwitchToCameraBegin(UCameraHandle* InCameraHandle);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Camera Hadnle Interface")
	void HandleSwitchToCameraFinish(UCameraHandle* InCameraHandle);
};
