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
	UCameraEdManager();

	/* IProcedureInterface*/
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IManagerInterface */
public:
	virtual bool IsEditorManager() override { return true; }

	/* UCameraEdManager */
protected:
	virtual void OnCopyViewportCamera(ACameraPoint* InCameraPoint);
	virtual void OnCameraPointPilotStateChanged(ACameraPoint* InCameraPoint, bool bIsPilot);
};
