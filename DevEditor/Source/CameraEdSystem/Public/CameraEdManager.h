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

	/* IProcedureBaseInterface*/
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* IProcedureInterface*/
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;
	virtual bool DoesSupportWorldType(EWorldType::Type InWorldType) override;

	/* UCameraEdManager */
protected:
	virtual void OnCopyViewportCamera(ACameraPointBase* InCameraPoint);
	virtual void OnCameraPointPilotStateChanged(ACameraPointBase* InCameraPoint, bool bIsPilot);
};
