// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraManager.h"

#include "CameraEdManager.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UCameraEdManager : public UCameraManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* UCameraEdManager */
protected:
	virtual void OnCopyViewportCamera(ACameraPointBase* InCameraPoint);
	virtual void OnCameraPointPilotStateChanged(ACameraPointBase* InCameraPoint, bool bIsPilot);
};
