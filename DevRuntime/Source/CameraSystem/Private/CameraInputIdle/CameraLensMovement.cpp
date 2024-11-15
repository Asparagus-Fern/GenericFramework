// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraInputIdle/CameraLensMovement.h"

#include "CameraManager.h"
#include "Manager/ManagerProxy.h"

UWorld* UCameraLensMovement::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("CommonButtonEvent: %s has a null OuterPrivate in UCommonButtonEvent::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (const UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
		{
			return CameraManager->GetWorld();
		}
		else
		{
			return GetOuter()->GetWorld();
		}
	}
	return nullptr;
}

void UCameraLensMovement::Tick(float DeltaTime)
{
	if (bIsMoving)
	{
		Super::Tick(DeltaTime);
	}
}

void UCameraLensMovement::NativeStartLensMovement()
{
	bIsMoving = true;
}

void UCameraLensMovement::NativeStopLensMovement()
{
	bIsMoving = false;
}
