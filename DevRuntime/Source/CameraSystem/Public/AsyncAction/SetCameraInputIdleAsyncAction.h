// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SetCameraInputIdleAsyncAction.generated.h"

class UCameraInputIdle;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCameraAutoSwitchDelegate, UCameraInputIdle*, CameraInputIdle);

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API USetCameraInputIdleAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static USetCameraInputIdleAsyncAction* SetCameraInputIdle(UCameraInputIdle* InCameraInputIdle);

public:
	UPROPERTY(BlueprintAssignable)
	FCameraAutoSwitchDelegate OnCameraAutoSwitchStart;

	UPROPERTY(BlueprintAssignable)
	FCameraAutoSwitchDelegate OnCameraAutoSwitchStop;

	UPROPERTY(BlueprintAssignable)
	FCameraAutoSwitchDelegate OnCameraAutoSwitchReset;

protected:
	virtual void CameraInputIdleReset(UCameraInputIdle* CameraInputIdle);
	virtual void CameraAutoSwitchStart(UCameraInputIdle* CameraInputIdle);
	virtual void CameraAutoSwitchStop(UCameraInputIdle* CameraInputIdle);
};
