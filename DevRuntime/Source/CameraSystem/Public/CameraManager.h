// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "CameraManager.generated.h"

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

public:
	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<FGameplayTag, ACameraPointBase*> CameraPoints;

	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UCameraHandle*> CurrentCameraHandles;

protected:
	bool CheckIsSwitching(const APlayerController* InPlayerController);
	UCameraHandle* GetCameraHandle(const APlayerController* InPlayerController);
	void HandleSwitchToCameraFinish(UCameraHandle* InCameraHandle);
};
