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
class UCameraSwitchMethod;
class ACameraPointBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_CameraPointDelegate, ACameraPointBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_CameraPointDelegate, ACameraPointBase*, InCameraPoint);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_CameraPointSwitchDelegate, ACameraPointBase*, UCameraSwitchMethod*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_CameraPointSwitchDelegate, ACameraPointBase*, InCameraPoint, UCameraSwitchMethod*, InMethod);

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* UCameraManager */
protected:
	virtual void AddCameraPoint(ACameraPointBase* InCameraPoint);
	virtual void RemoveCameraPoint(ACameraPointBase* InCameraPoint);
	virtual void HandleSwitchToCameraFinish(UCameraSwitchMethod* InCameraHandle);

public:
	CAMERASYSTEM_API bool CanSwitchToCamera(FGameplayTag InCameraTag) const;

	CAMERASYSTEM_API ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag) const;

	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, FVector Location, FRotator Rotation, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraSwitchMethod* InSwitchCameraMethod, FSimpleDelegate OnFinish = FSimpleDelegate());

	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraSwitchMethod* InSwitchCameraMethod, FSimpleDelegate OnFinish = FSimpleDelegate());

	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraSwitchMethod* InSwitchCameraMethod, FSimpleDelegate OnFinish = FSimpleDelegate());

	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, FGameplayTag InCameraTag, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, FGameplayTag InCameraTag, UCameraSwitchMethod* InSwitchCameraMethod, FSimpleDelegate OnFinish = FSimpleDelegate());

	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, FSimpleDelegate OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API virtual UCameraSwitchMethod* SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraSwitchMethod* InSwitchCameraMethod, FSimpleDelegate OnFinish = FSimpleDelegate());

	CAMERASYSTEM_API UCameraSwitchMethod* SwitchToCurrent(const int32 InPlayerIndex, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API UCameraSwitchMethod* SwitchToCurrent(const int32 InPlayerIndex, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API UCameraSwitchMethod* SwitchToPrevious(const int32 InPlayerIndex, TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	CAMERASYSTEM_API UCameraSwitchMethod* SwitchToPrevious(const int32 InPlayerIndex, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

private:
	bool IsSwitching(const APlayerController* InPlayerController);
	UCameraSwitchMethod* GetCameraHandle(const APlayerController* InPlayerController);
	void UpdateCameraTag(int32 InPlayerIndex, FGameplayTag InCameraTag);

public:
	inline static FDelegate_CameraPointDelegate Delegate_OnCameraPointRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_CameraPointDelegate BPDelegate_OnCameraPointRegister;

	inline static FDelegate_CameraPointDelegate Delegate_OnCameraPointUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_CameraPointDelegate BPDelegate_OnCameraPointUnRegister;

	inline static FDelegate_CameraPointSwitchDelegate Delegate_OnCameraSwitchBegin;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_CameraPointSwitchDelegate BPDelegate_OnCameraSwitchBegin;

	inline static FDelegate_CameraPointSwitchDelegate Delegate_OnCameraSwitchEnd;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_CameraPointSwitchDelegate BPDelegate_OnCameraSwitchEnd;

protected:
	/* 已注册的相机点位 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<FGameplayTag, ACameraPointBase*> CameraPoints;

	/* 当前正在进行的切换相机句柄 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UCameraSwitchMethod*> CurrentCameraMethods;

	/* 当前的相机标签 */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(Categories="Camera"))
	TMap<int32, FGameplayTag> CurrentCameraTag;

	/* 上一次的相机标签 */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(Categories="Camera"))
	TMap<int32, FGameplayTag> PreviousCameraTag;
};
