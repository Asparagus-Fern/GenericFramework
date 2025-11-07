// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CameraPoint/CameraPointBase.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericCameraSubsystem.generated.h"

class UCameraLensMovement;
class UCameraComponent;
class UGenericCameraSwitchMethod;
class ACameraPointBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_CameraPointDelegate, ACameraPointBase*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_CameraPointDelegate, ACameraPointBase*, InCameraPoint);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_CameraPointSwitchDelegate, ACameraPointBase*, UGenericCameraSwitchMethod*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_CameraPointSwitchDelegate, ACameraPointBase*, InCameraPoint, UGenericCameraSwitchMethod*, InMethod);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericCameraSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static GENERICCAMERASYSTEM_API UGenericCameraSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* UCameraManager */
protected:
	virtual void AddCameraPoint(ACameraPointBase* InCameraPoint);
	virtual void RemoveCameraPoint(ACameraPointBase* InCameraPoint);
	virtual void HandleSwitchToCameraFinish(UGenericCameraSwitchMethod* InCameraHandle);

public:
	GENERICCAMERASYSTEM_API bool CanSwitchToCamera(FGameplayTag InCameraTag) const;

	GENERICCAMERASYSTEM_API ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag) const;

	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, const FVector& Location, const FRotator& Rotation, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, const FVector& Location, const FRotator& Rotation, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, const ACameraActor* InCameraActor, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, const ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, UCameraComponent* InCameraComponent, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, FGameplayTag InCameraTag, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, ACameraPointBase* InCameraPoint, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCamera(APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCurrent(APlayerController* InPlayer, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToCurrent(APlayerController* InPlayer, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToPrevious(APlayerController* InPlayer, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish = FSimpleDelegate());
	GENERICCAMERASYSTEM_API UGenericCameraSwitchMethod* SwitchToPrevious(APlayerController* InPlayer, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish = FSimpleDelegate());

private:
	bool IsSwitching(const APlayerController* InPlayerController);
	UGenericCameraSwitchMethod* GetCameraSwitchMethod(const APlayerController* InPlayerController);
	void UpdateCameraTag(APlayerController* InPlayer, FGameplayTag InCameraTag);

public:
	GENERICCAMERASYSTEM_API inline static FDelegate_CameraPointDelegate Delegate_OnCameraPointRegister;
	UPROPERTY(BlueprintAssignable, DisplayName="OnCameraPointRegister")
	FBPDelegate_CameraPointDelegate BPDelegate_OnCameraPointRegister;

	GENERICCAMERASYSTEM_API inline static FDelegate_CameraPointDelegate Delegate_OnCameraPointUnRegister;
	UPROPERTY(BlueprintAssignable, DisplayName="OnCameraPointUnRegister")
	FBPDelegate_CameraPointDelegate BPDelegate_OnCameraPointUnRegister;

	GENERICCAMERASYSTEM_API inline static FDelegate_CameraPointSwitchDelegate Delegate_OnCameraSwitchBegin;
	UPROPERTY(BlueprintAssignable, DisplayName="OnCameraSwitchBegin")
	FBPDelegate_CameraPointSwitchDelegate BPDelegate_OnCameraSwitchBegin;

	GENERICCAMERASYSTEM_API inline static FDelegate_CameraPointSwitchDelegate Delegate_OnCameraSwitchEnd;
	UPROPERTY(BlueprintAssignable, DisplayName="OnCameraSwitchEnd")
	FBPDelegate_CameraPointSwitchDelegate BPDelegate_OnCameraSwitchEnd;

protected:
	/* 已注册的相机点位 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<FGameplayTag, ACameraPointBase*> CameraPoints;

	/* 当前正在进行的切换相机句柄 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UGenericCameraSwitchMethod*> CurrentCameraMethods;

	/* 当前的相机标签 */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(Categories="Camera"))
	TMap<APlayerController*, FGameplayTag> CurrentCameraTag;

	/* 上一次的相机标签 */
	UPROPERTY(BlueprintReadOnly, Transient, meta=(Categories="Camera"))
	TMap<APlayerController*, FGameplayTag> PreviousCameraTag;
};
