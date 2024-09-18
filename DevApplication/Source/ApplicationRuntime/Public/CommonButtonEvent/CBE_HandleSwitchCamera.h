// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/CommonButtonEvent.h"
#include "CBE_HandleSwitchCamera.generated.h"

class UCameraHandle;


/**
 * 处理相机的切换
 */
UCLASS(MinimalAPI)
class UCBE_HandleSwitchCamera : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	UCBE_HandleSwitchCamera();

	/* CommonButtonEvent */
public:
	virtual bool CanExecuteButtonEvent_Implementation() override;
	virtual void ExecuteButtonEvent_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TargetPlayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera"))
	FGameplayTag TargetCameraTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UCameraHandle* TargetCameraHandle = nullptr;
};
