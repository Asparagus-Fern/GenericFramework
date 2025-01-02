// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CameraPoint/CameraPointBase.h"
#include "Manager/CoreInternalManager.h"
#include "CameraManager.generated.h"

class UCameraLensMovement;
class UInputIdle;
class UCameraInputIdle;
class UCameraComponent;
class UCameraHandle;
class ACameraPointBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_CameraPointDelegate, ACameraPointBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_CameraPointDelegate, ACameraPointBase*, InCameraPoint);

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UCameraManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

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
	inline static FDelegate_CameraPointDelegate Delegate_OnCameraPointRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_CameraPointDelegate BPDelegate_OnCameraPointRegister;

	inline static FDelegate_CameraPointDelegate Delegate_OnCameraPointUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_CameraPointDelegate BPDelegate_OnCameraPointUnRegister;

public:
	virtual void AddCameraPoint(ACameraPointBase* InCameraPoint);
	virtual void RemoveCameraPoint(ACameraPointBase* InCameraPoint);
	ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag) const;
	bool CanCameraSwitch(FGameplayTag InCameraTag) const;

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
public:
	DECLARE_EVENT_OneParam(UCameraManager, FCameraAutoSwitchDelegate, UCameraInputIdle*)

	static FCameraAutoSwitchDelegate OnCameraInputIdleReset;
	static FCameraAutoSwitchDelegate OnCameraAutoSwitchStart;
	static FCameraAutoSwitchDelegate OnCameraAutoSwitchStop;
	static FCameraAutoSwitchDelegate OnCameraLensMovementStart;
	static FCameraAutoSwitchDelegate OnCameraLensMovementStop;

public:
	bool SetCameraInputIdle(UCameraInputIdle* InCameraInputIdle);

protected:
	/* 当前的相机空闲数据 */
	UPROPERTY(Transient, BlueprintReadOnly)
	UCameraInputIdle* CameraInputIdle = nullptr;

	/* 计数当前相机自动切换的下标 */
	int32 CameraAutoSwitchIndex = 0;

	/* 执行下一次切换的延迟时间句柄 */
	FTimerHandle AutoSwitchCameraHandle;

	UPROPERTY(Transient)
	UCameraLensMovement* CameraLensMovement = nullptr;

protected:
	virtual void OnInputIdleStart(UInputIdle* InputIdle);
	virtual void OnInputIdleStop(UInputIdle* InputIdle);

	virtual void HandleCameraAutoSwitch();
	virtual void HandleCameraLensMovement();
};
