// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreManager.h"
#include "CameraManager.generated.h"

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

public:
	UFUNCTION(BlueprintPure)
	ACameraPointBase* GetCameraPoint(FGameplayTag InCameraTag) const;

	UFUNCTION(BlueprintCallable)
	void SwitchToCamera(FGameplayTag InCameraTag);

	UFUNCTION(BlueprintCallable)
	void SwitchToCameraByPlayerController(FGameplayTag InCameraTag, APlayerController* PlayerController);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, ACameraPointBase*> CameraPoints;
};
