// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraManager.h"

#include "CameraEdManager.generated.h"

/**
 * 
 */
UCLASS()
class CAMERAEDSYSTEM_API UCameraEdManager : public UCameraManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* IProcedureBaseInterface*/
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UCameraEdManager */
protected:
	virtual void OnCopyViewportCamera(ACameraPointBase* InCameraPoint);
	virtual void OnCameraPointPilotStateChanged(ACameraPointBase* InCameraPoint, bool bIsPilot);
};
