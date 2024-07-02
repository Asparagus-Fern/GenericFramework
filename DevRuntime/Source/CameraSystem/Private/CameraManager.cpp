// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "CameraHandle.h"
#include "CameraSystemType.h"
#include "CameraPoint/CameraPointBase.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

UCameraManager::UCameraManager()
{
}

FText UCameraManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Camera Manager");
}

void UCameraManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UCameraManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	CameraPoints.Reset();
}

void UCameraManager::AddCameraPoint(FGameplayTag InCameraTag, ACameraPointBase* InCameraPoint)
{
	if (InCameraTag.IsValid())
	{
		CameraPoints.Add(InCameraTag, InCameraPoint);
	}
}

void UCameraManager::RemoveCameraPoint(FGameplayTag InCameraTag)
{
	CameraPoints.Remove(InCameraTag);
}

ACameraPointBase* UCameraManager::GetCameraPoint(const FGameplayTag InCameraTag) const
{
	if (CameraPoints.Contains(InCameraTag))
	{
		return CameraPoints.FindRef(InCameraTag);
	}

	return nullptr;
}

void UCameraManager::SwitchToCamera(FGameplayTag InCameraTag)
{
	if (!InCameraTag.IsValid())
	{
		DEBUG(Debug_Viewport, Error, TEXT("CameraTag Is NULL"))
		return;
	}

	if (ACameraPointBase* FoundCameraPoint = GetCameraPoint(InCameraTag))
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			SwitchToCameraByPlayerController(InCameraTag, PlayerController);
		}
	}
}

void UCameraManager::SwitchToCameraByPlayerController(FGameplayTag InCameraTag, APlayerController* PlayerController)
{
	/* Check */
	if (!InCameraTag.IsValid())
	{
		DEBUG(Debug_Viewport, Error, TEXT("CameraTag Is NULL"))
		return;
	}

	if (!PlayerController)
	{
		DEBUG(Debug_Viewport, Error, TEXT("PlayerController Is NULL"))
		return;
	}

	/* Switch */
	if (ACameraPointBase* FoundCameraPoint = CameraPoints.FindRef(InCameraTag))
	{
		FCameraSystemDelegates::PreSwitchCamera.Broadcast(FoundCameraPoint);

		if (IsValid(FoundCameraPoint->CameraHandle))
		{
			FoundCameraPoint->CameraHandle->HandleSwitchToCameraPoint(PlayerController, FoundCameraPoint);
		}

		FCameraSystemDelegates::PostSwitchCamera.Broadcast(FoundCameraPoint);
	}
}

#undef LOCTEXT_NAMESPACE
