// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraSwitchInterface.generated.h"

class UCameraSwitchMethod;

UINTERFACE()
class UCameraSwitchInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAMERASYSTEM_API ICameraSwitchInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Camera Hadnle Interface")
	void HandleSwitchToCameraBegin(UCameraSwitchMethod* InCameraSwitchMethod);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Camera Hadnle Interface")
	void HandleSwitchToCameraFinish(UCameraSwitchMethod* InCameraSwitchMethod);
};
