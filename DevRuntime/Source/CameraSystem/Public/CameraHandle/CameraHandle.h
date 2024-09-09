// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "Object/CommonObject.h"
#include "CameraHandle.generated.h"

class UCameraComponent;
class ACameraPointBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchCameraFinish);

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class CAMERASYSTEM_API UCameraHandle : public UCommonObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetWorld() const override;

public:
	UFUNCTION(BlueprintCallable)
	void Reset();

public:
	/* 处理相机过渡 */
	UFUNCTION(BlueprintNativeEvent)
	bool HandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint);
	virtual bool NativeHandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint, FSimpleDelegate OnFinish = FSimpleDelegate());

	/* 当相机过渡被打断时 */
	UFUNCTION(BlueprintNativeEvent)
	void OnSwitchToCameraPointReset();
	virtual void NativeOnSwitchToCameraPointReset();

	/* 当相机过渡完成时 */
	UFUNCTION(BlueprintNativeEvent)
	void OnSwitchToCameraPointFinish();
	virtual void NativeOnSwitchToCameraPointFinish();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetSwitchDuration();
	
public:
	UPROPERTY(BlueprintReadOnly)
	APlayerController* OwnerPlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACameraPointBase* TargetCameraPoint = nullptr;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FCameraHandleDelegate, UCameraHandle*)
	static FCameraHandleDelegate OnSwitchCameraBegin;
	static FCameraHandleDelegate OnSwitchCameraFinish;

protected:
	FSimpleDelegate OnHandleFinish;
};
