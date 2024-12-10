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
	/*
	 * true：使用CameraActor的ActorTag查找相机进行切换
	 * false：查找对应的CameraPoint的CameraTag进行切换
	 */
	UPROPERTY(EditAnywhere)
	bool bUseUnrealCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TargetPlayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Camera", EditConditionHides, EditCondition = "!bUseUnrealCamera"))
	FGameplayTag TargetCameraGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bUseUnrealCamera"))
	FName TargetCameraNameTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UCameraHandle* TargetCameraHandle = nullptr;
};
