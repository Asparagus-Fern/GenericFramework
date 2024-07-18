// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "CameraManager.generated.h"

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
	UCameraManager();

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UCameraManager */
public:
	virtual void AddCameraPoint(FGameplayTag InCameraTag, ACameraPointBase* InCameraPoint);
	virtual void RemoveCameraPoint(FGameplayTag InCameraTag);
	ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag) const;

	bool CanSwitchToCamera(FGameplayTag InCameraTag) const;
	virtual void SwitchToCamera(FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle);
	virtual void SwitchToCamera(APlayerController* PlayerController, FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	TMap<FGameplayTag, ACameraPointBase*> CameraPoints;
};
