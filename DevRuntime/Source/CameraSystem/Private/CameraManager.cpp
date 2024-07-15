// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "CameraSystemType.h"
#include "CameraPoint/CameraPointBase.h"
#include "Handle/CameraHandle.h"

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

bool UCameraManager::CanSwitchToCamera(const FGameplayTag InCameraTag) const
{
	return InCameraTag.IsValid() && IsValid(GetCameraPoint(InCameraTag));
}

void UCameraManager::SwitchToCamera(const FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle)
{
	if (!InCameraTag.IsValid() || !IsValid(SwitchCameraHandle))
	{
		DEBUG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
		return;
	}

	if (ACameraPointBase* FoundCameraPoint = GetCameraPoint(InCameraTag))
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			SwitchToCamera(PlayerController, InCameraTag, SwitchCameraHandle);
		}
	}
	else
	{
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
	}
}

void UCameraManager::SwitchToCamera(APlayerController* PlayerController, const FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle)
{
	if (!InCameraTag.IsValid() || !PlayerController || !IsValid(SwitchCameraHandle))
	{
		DEBUG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
		return;
	}

	/* Switch */
	if (ACameraPointBase* FoundCameraPoint = CameraPoints.FindRef(InCameraTag))
	{
		FCameraSystemDelegates::PreSwitchCamera.Broadcast(FoundCameraPoint);
		SwitchCameraHandle->HandleSwitchToCameraPoint(PlayerController, FoundCameraPoint);
		FCameraSystemDelegates::PostSwitchCamera.Broadcast(FoundCameraPoint);
	}
}

#undef LOCTEXT_NAMESPACE
