// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "CameraSystemType.h"
#include "CineCameraComponent.h"
#include "CameraPoint/CameraPoint.h"
#include "CameraPoint/CameraPointBase.h"
#include "CameraPoint/CineCameraPoint.h"
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

void UCameraManager::SwitchToCamera(UCameraComponent* InCameraComponent, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	SwitchToCamera(InCameraComponent, NewObject<UCameraHandle>(this, InCameraHandleClass));
}

void UCameraManager::SwitchToCamera(UCameraComponent* InCameraComponent, UCameraHandle* SwitchCameraHandle)
{
	if (!IsValid(InCameraComponent) || !IsValid(SwitchCameraHandle))
	{
		DEBUG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
		return;
	}

	FVector a = InCameraComponent->GetComponentLocation();
	FRotator b = InCameraComponent->GetComponentRotation();

	ACameraPointBase* SpawnCameraPoint;
	if (Cast<UCineCameraComponent>(InCameraComponent))
	{
		SpawnCameraPoint = GetWorld()->SpawnActor<ACineCameraPoint>(InCameraComponent->GetComponentLocation(), InCameraComponent->GetComponentRotation());
	}
	else
	{
		SpawnCameraPoint = GetWorld()->SpawnActor<ACameraPoint>(InCameraComponent->GetComponentLocation(), InCameraComponent->GetComponentRotation());
	}
	
	SpawnCameraPoint->SetCameraComponent(InCameraComponent);
	SwitchToCamera(SpawnCameraPoint, SwitchCameraHandle);
}

void UCameraManager::SwitchToCamera(FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (InCameraHandleClass)
	{
		SwitchToCamera(InCameraTag, NewObject<UCameraHandle>(this, InCameraHandleClass));
	}
	else
	{
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
	}
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
		SwitchToCamera(FoundCameraPoint, SwitchCameraHandle);
	}
	else
	{
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
	}
}

void UCameraManager::SwitchToCamera(ACameraPointBase* InCameraPoint, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (InCameraHandleClass)
	{
		SwitchToCamera(InCameraPoint, NewObject<UCameraHandle>(this, InCameraHandleClass));
	}
	else
	{
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
	}
}

void UCameraManager::SwitchToCamera(ACameraPointBase* InCameraPoint, UCameraHandle* SwitchCameraHandle)
{
	if (!IsValid(InCameraPoint) || !IsValid(SwitchCameraHandle))
	{
		DEBUG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
		return;
	}

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		SwitchToCamera(PlayerController, InCameraPoint, SwitchCameraHandle);
	}
}

void UCameraManager::SwitchToCamera(APlayerController* PlayerController, FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (IsValid(InCameraHandleClass))
	{
		SwitchToCamera(PlayerController, GetCameraPoint(InCameraTag), NewObject<UCameraHandle>(this, InCameraHandleClass));
	}
	else
	{
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
	}
}

void UCameraManager::SwitchToCamera(APlayerController* PlayerController, FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle)
{
	SwitchToCamera(PlayerController, GetCameraPoint(InCameraTag), SwitchCameraHandle);
}

void UCameraManager::SwitchToCamera(APlayerController* PlayerController, ACameraPointBase* InCameraPoint, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (IsValid(InCameraHandleClass))
	{
		SwitchToCamera(PlayerController, InCameraPoint, NewObject<UCameraHandle>(this, InCameraHandleClass));
	}
	else
	{
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
	}
}

void UCameraManager::SwitchToCamera(APlayerController* PlayerController, ACameraPointBase* InCameraPoint, UCameraHandle* SwitchCameraHandle)
{
	if (!PlayerController || !IsValid(InCameraPoint) || !IsValid(SwitchCameraHandle))
	{
		DEBUG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(nullptr);
		return;
	}

	FCameraSystemDelegates::PreSwitchCamera.Broadcast(InCameraPoint);
	SwitchCameraHandle->HandleSwitchToCameraPoint(PlayerController, InCameraPoint);
	FCameraSystemDelegates::PostSwitchCamera.Broadcast(InCameraPoint);
}

#undef LOCTEXT_NAMESPACE
