// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "CameraAutoSwitch.h"
#include "CameraHandle.h"
#include "CameraManagerSetting.h"
#include "CineCameraComponent.h"
#include "Camera/CameraActor.h"
#include "CameraPoint/CameraPoint.h"
#include "CameraPoint/CameraPointBase.h"
#include "CameraPoint/CineCameraPoint.h"
#include "Input/InputManager.h"
#include "Kismet/GameplayStatics.h"
#include "Slate/SceneViewport.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

bool UCameraManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UCameraManagerSetting::Get()->bEnableSubsystem;
}

void UCameraManager::NativeOnActived()
{
	Super::NativeOnActived();
	UCameraHandle::OnSwitchCameraFinish.AddUObject(this, &UCameraManager::HandleSwitchToCameraFinish);
}

void UCameraManager::NativeOnInactived()
{
	Super::NativeOnInactived();
	UCameraHandle::OnSwitchCameraFinish.RemoveAll(this);
}

void UCameraManager::AddCameraPoint(FGameplayTag InCameraTag, ACameraPointBase* InCameraPoint)
{
	if (InCameraTag.IsValid())
	{
		CameraPoints.FindOrAdd(InCameraTag, InCameraPoint);
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

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraHandleClass)
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, Location, Rotation, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!IsValid(SwitchCameraHandle))
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	ACameraPoint* SpawnCameraPoint = GetWorld()->SpawnActor<ACameraPoint>(Location, Rotation);
	return SwitchToCamera(InPlayerIndex, SpawnCameraPoint, SwitchCameraHandle, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraActor || !InCameraHandleClass)
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraActor->GetCameraComponent(), InCameraHandleClass, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!InCameraActor || !IsValid(SwitchCameraHandle))
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraActor->GetCameraComponent(), SwitchCameraHandle, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraComponent) || !InCameraHandleClass)
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraComponent, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraComponent) || !IsValid(SwitchCameraHandle))
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

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
	return SwitchToCamera(InPlayerIndex, SpawnCameraPoint, SwitchCameraHandle, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FGameplayTag InCameraTag, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraTag.IsValid() || !InCameraHandleClass)
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}


	return SwitchToCamera(InPlayerIndex, InCameraTag, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!InCameraTag.IsValid() || !IsValid(SwitchCameraHandle) || !IsValid(GetCameraPoint(InCameraTag)))
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, GetCameraPoint(InCameraTag), SwitchCameraHandle, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraPoint) || !InCameraHandleClass)
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraPoint, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraPoint) || !IsValid(SwitchCameraHandle))
	{
		LOG(Debug_Camera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(InCameraPoint, InPlayerIndex))
	{
		if (CheckIsSwitching(PC))
		{
			UCameraHandle* CameraHandle = GetCameraHandle(PC);
			CameraHandle->NativeOnSwitchToCameraPointReset();
		}

		CurrentCameraHandles.AddUnique(SwitchCameraHandle);
		SwitchCameraHandle->NativeHandleSwitchToCameraPoint(PC, InCameraPoint, OnFinish);
		return SwitchCameraHandle;
	}

	return nullptr;
}

bool UCameraManager::CheckIsSwitching(const APlayerController* InPlayerController)
{
	ensure(InPlayerController);

	if (IsValid(InPlayerController))
	{
		for (const auto& CurrentCameraHandle : CurrentCameraHandles)
		{
			if (CurrentCameraHandle->OwnerPlayerController == InPlayerController)
			{
				return true;
			}
		}
	}

	return false;
}

UCameraHandle* UCameraManager::GetCameraHandle(const APlayerController* InPlayerController)
{
	for (const auto& CurrentCameraHandle : CurrentCameraHandles)
	{
		if (CurrentCameraHandle->OwnerPlayerController == InPlayerController)
		{
			return CurrentCameraHandle;
		}
	}
	return nullptr;
}

void UCameraManager::HandleSwitchToCameraFinish(UCameraHandle* InCameraHandle)
{
	if (!IsValid(InCameraHandle))
	{
		return;
	}

	if (CurrentCameraHandles.Contains(InCameraHandle))
	{
		CurrentCameraHandles.Remove(InCameraHandle);
	}
}

bool UCameraManager::SetCameraAutoSwitch(UCameraAutoSwitch* InCameraAutoSwitch)
{
	if (UInputManager* InputManager = GetManager<UInputManager>())
	{
		if (IsValid(CameraAutoSwitch) && !IsValid(InCameraAutoSwitch))
		{
			InputManager->UnRegisterIdleData(CameraAutoSwitch);
			CameraAutoSwitch = nullptr;
			return true;
		}

		if (IsValid(InCameraAutoSwitch))
		{
			if (IsValid(CameraAutoSwitch))
			{
				InputManager->UnRegisterIdleData(CameraAutoSwitch);
			}

			if (InCameraAutoSwitch->AutoSwitchTags.IsEmpty() || !IsValid(InCameraAutoSwitch->CameraHandle) || InCameraAutoSwitch->TimeInterval < 0.f)
			{
				return false;
			}

			CameraAutoSwitch = InCameraAutoSwitch;
			InputManager->RegisterIdleData(CameraAutoSwitch, FInputIdleDelegate::CreateUObject(this, &UCameraManager::OnCameraAutoSwitchStart), FInputIdleDelegate::CreateUObject(this, &UCameraManager::OnCameraAutoSwitchStop));
			return true;
		}
	}

	return false;
}

void UCameraManager::OnCameraAutoSwitchStart(UInputIdle* InputIdle)
{
	if (CameraAutoSwitch == InputIdle)
	{
		GetWorld()->GetTimerManager().SetTimer(CameraAutoSwitchHandle, FTimerDelegate::CreateUObject(this, &UCameraManager::AutoSwitchCamera), CameraAutoSwitch->TimeInterval, true);
		AutoSwitchCamera();
	}
}

void UCameraManager::AutoSwitchCamera()
{
	auto Switch = [this]()
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PC = Iterator->Get();
			SwitchToCamera(UGameplayStatics::GetPlayerControllerID(PC), CameraAutoSwitch->AutoSwitchTags[CameraAutoSwitchIndex], CameraAutoSwitch->CameraHandle);
		}
	};

	if (IsValid(CameraAutoSwitch))
	{
		if (!CameraAutoSwitch->AutoSwitchTags.IsValidIndex(CameraAutoSwitchIndex))
		{
			CameraAutoSwitchIndex = 0;
		}

		if (!CameraAutoSwitch->AutoSwitchTags[CameraAutoSwitchIndex].IsValid())
		{
			CameraAutoSwitchIndex++;
			AutoSwitchCamera();
			return;
		}

		Switch();
		CameraAutoSwitchIndex++;
	}
}

void UCameraManager::OnCameraAutoSwitchStop(UInputIdle* InputIdle)
{
	GetWorld()->GetTimerManager().ClearTimer(CameraAutoSwitchHandle);
	CameraAutoSwitchHandle.Invalidate();
	CameraAutoSwitchIndex = 0;
}

#undef LOCTEXT_NAMESPACE
