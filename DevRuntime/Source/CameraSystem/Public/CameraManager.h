// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "CameraManager.generated.h"

class UCameraLensMovement;
class UInputIdle;
class UCameraInputIdle;
class UCameraComponent;
class UCameraHandle;
class ACameraPointBase;

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UCameraManager : public UCoreManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UCameraManager */
public:
	/* 已注册的相机点位 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<FGameplayTag, ACameraPointBase*> CameraPoints;

	/* 当前正在进行的切换相机句柄 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UCameraHandle*> CurrentCameraHandles;

	/* 当前的相机标签 */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(Categories="Camera"))
	TMap<int32, FGameplayTag> CurrentCameraTag;

	/* 上一次的相机标签 */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(Categories="Camera"))
	TMap<int32, FGameplayTag> PreviousCameraTag;

public:
	virtual void AddCameraPoint(FGameplayTag InCameraTag, ACameraPointBase* InCameraPoint);
	virtual void RemoveCameraPoint(FGameplayTag InCameraTag);
	ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag) const;

public:
	bool CanSwitchToCamera(FGameplayTag InCameraTag) const;

	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, FVector Location, FRotator Rotation, TSubclassOf<UCameraHandle> InCameraHandleClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraHandle* SwitchCameraHandle, FSimpleDelegate OnFinish = FSimpleDelegate());

	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, TSubclassOf<UCameraHandle> InCameraHandleClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* SwitchCameraHandle, FSimpleDelegate OnFinish = FSimpleDelegate());

	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, TSubclassOf<UCameraHandle> InCameraHandleClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* SwitchCameraHandle, FSimpleDelegate OnFinish = FSimpleDelegate());

	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> InCameraHandleClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle, FSimpleDelegate OnFinish = FSimpleDelegate());

	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraHandle> InCameraHandleClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	virtual UCameraHandle* SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* SwitchCameraHandle, FSimpleDelegate OnFinish = FSimpleDelegate());

	UCameraHandle* SwitchToCurrent(const int32 InPlayerIndex, TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	UCameraHandle* SwitchToCurrent(const int32 InPlayerIndex, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	UCameraHandle* SwitchToPrevious(const int32 InPlayerIndex, TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	UCameraHandle* SwitchToPrevious(const int32 InPlayerIndex, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate& OnFinish = FSimpleDelegate());

protected:
	bool CheckIsSwitching(const APlayerController* InPlayerController);
	UCameraHandle* GetCameraHandle(const APlayerController* InPlayerController);
	void UpdateCameraTag(int32 InPlayerIndex, FGameplayTag InCameraTag);
	void HandleSwitchToCameraFinish(UCameraHandle* InCameraHandle);

	/* UCameraInputIdle */
protected:
	/* 当前的相机空闲数据 */
	UPROPERTY(Transient, BlueprintReadOnly)
	UCameraInputIdle* CameraInputIdle = nullptr;

public:
	bool SetCameraInputIdle(UCameraInputIdle* InCameraInputIdle);

	DECLARE_MULTICAST_DELEGATE_OneParam(FCameraAutoSwitchDelegate, UCameraInputIdle*)
	static FCameraAutoSwitchDelegate OnCameraInputIdleReset;
	static FCameraAutoSwitchDelegate OnCameraAutoSwitchStart;
	static FCameraAutoSwitchDelegate OnCameraAutoSwitchStop;
	static FCameraAutoSwitchDelegate OnCameraLensMovementStart;
	static FCameraAutoSwitchDelegate OnCameraLensMovementStop;

protected:
	virtual void OnInputIdleStart(UInputIdle* InputIdle);
	virtual void OnInputIdleStop(UInputIdle* InputIdle);

protected:
	/* 计数当前相机自动切换的下标 */
	int32 CameraAutoSwitchIndex = 0;

	/* 执行下一次切换的延迟时间句柄 */
	FTimerHandle AutoSwitchCameraHandle;

	UPROPERTY(Transient)
	UCameraLensMovement* CameraLensMovement = nullptr;

protected:
	virtual void HandleCameraAutoSwitch();
	virtual void HandleCameraLensMovement();

public:
};
