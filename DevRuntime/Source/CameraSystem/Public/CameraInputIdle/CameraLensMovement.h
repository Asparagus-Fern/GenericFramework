// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/TickableObject.h"
#include "CameraLensMovement.generated.h"

/**
 * 相机运镜
 */
UCLASS(Abstract, EditInlineNew)
class CAMERASYSTEM_API UCameraLensMovement : public UTickableObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetWorld() const override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NativeStartLensMovement();
	virtual void NativeStopLensMovement();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 10.f;

protected:
	bool bIsMoving = false;
};
