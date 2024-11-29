// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "CameraManagerSetting.h"
#include "CineCameraComponent.h"
#include "Camera/CameraActor.h"
#include "CameraHandle/CameraHandle.h"
#include "CameraInputIdle/CameraInputIdle.h"
#include "CameraInputIdle/CameraLensMovement.h"
#include "CameraPoint/CameraPoint.h"
#include "CameraPoint/CameraPointBase.h"
#include "CameraPoint/CineCameraPoint.h"
#include "Input/InputManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerProxy.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

UCameraManager::FCameraPointDelegate UCameraManager::OnCameraPointRegister;
UCameraManager::FCameraPointDelegate UCameraManager::OnCameraPointUnRegister;

UCameraManager::FCameraAutoSwitchDelegate UCameraManager::OnCameraInputIdleReset;
UCameraManager::FCameraAutoSwitchDelegate UCameraManager::OnCameraAutoSwitchStart;
UCameraManager::FCameraAutoSwitchDelegate UCameraManager::OnCameraAutoSwitchStop;
UCameraManager::FCameraAutoSwitchDelegate UCameraManager::OnCameraLensMovementStart;
UCameraManager::FCameraAutoSwitchDelegate UCameraManager::OnCameraLensMovementStop;

bool UCameraManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UCameraManagerSetting::Get()->GetEnableManager();
}

void UCameraManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	ACameraPointBase::OnCameraPointRegister.AddUObject(this, &UCameraManager::AddCameraPoint);
	ACameraPointBase::OnCameraPointUnRegister.AddUObject(this, &UCameraManager::RemoveCameraPoint);
	UCameraHandle::OnSwitchCameraFinish.AddUObject(this, &UCameraManager::HandleSwitchToCameraFinish);
}

void UCameraManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	ACameraPointBase::OnCameraPointRegister.RemoveAll(this);
	ACameraPointBase::OnCameraPointUnRegister.RemoveAll(this);
	UCameraHandle::OnSwitchCameraFinish.RemoveAll(this);
}

bool UCameraManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UCameraManager::AddCameraPoint(ACameraPointBase* InCameraPoint)
{
	if (IsValid(InCameraPoint) && InCameraPoint->CameraTag.IsValid() && !CameraPoints.Contains(InCameraPoint->CameraTag))
	{
		CameraPoints.FindOrAdd(InCameraPoint->CameraTag, InCameraPoint);
		OnCameraPointRegister.Broadcast(InCameraPoint);
	}
}

void UCameraManager::RemoveCameraPoint(ACameraPointBase* InCameraPoint)
{
	if (IsValid(InCameraPoint) && InCameraPoint->CameraTag.IsValid() && CameraPoints.Contains(InCameraPoint->CameraTag))
	{
		CameraPoints.Remove(InCameraPoint->CameraTag);
		OnCameraPointUnRegister.Broadcast(InCameraPoint);
	}
}

ACameraPointBase* UCameraManager::GetCameraPoint(const FGameplayTag InCameraTag) const
{
	if (CameraPoints.Contains(InCameraTag))
	{
		return CameraPoints.FindRef(InCameraTag);
	}

	return nullptr;
}

bool UCameraManager::CanCameraSwitch(FGameplayTag InCameraTag) const
{
	return IsValid(GetCameraPoint(InCameraTag));
}

bool UCameraManager::CanSwitchToCamera(const FGameplayTag InCameraTag) const
{
	return InCameraTag.IsValid() && IsValid(GetCameraPoint(InCameraTag));
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraHandleClass)
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, Location, Rotation, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!IsValid(SwitchCameraHandle))
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
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
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraActor->GetCameraComponent(), InCameraHandleClass, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!InCameraActor || !IsValid(SwitchCameraHandle))
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraActor->GetCameraComponent(), SwitchCameraHandle, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraComponent) || !InCameraHandleClass)
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraComponent, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraComponent) || !IsValid(SwitchCameraHandle))
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
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
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}


	return SwitchToCamera(InPlayerIndex, InCameraTag, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!InCameraTag.IsValid() || !IsValid(SwitchCameraHandle) || !IsValid(GetCameraPoint(InCameraTag)))
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, GetCameraPoint(InCameraTag), SwitchCameraHandle, OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraPoint) || !InCameraHandleClass)
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraPoint, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraPoint) || !IsValid(SwitchCameraHandle))
	{
		DLOG(DLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	if (IsValid(CameraLensMovement))
	{
		OnCameraLensMovementStop.Broadcast(CameraInputIdle);
		CameraLensMovement->NativeStopLensMovement();
		CameraLensMovement = nullptr;
	}

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(InCameraPoint, InPlayerIndex))
	{
		if (CheckIsSwitching(PC))
		{
			UCameraHandle* CameraHandle = GetCameraHandle(PC);
			CameraHandle->NativeOnSwitchToCameraPointReset();
		}

		CurrentCameraHandles.AddUnique(SwitchCameraHandle);

		if (InCameraPoint->CameraTag.IsValid())
			UpdateCameraTag(InPlayerIndex, InCameraPoint->CameraTag);

		SwitchCameraHandle->NativeHandleSwitchToCameraPoint(PC, InCameraPoint, OnFinish);
		return SwitchCameraHandle;
	}

	return nullptr;
}

UCameraHandle* UCameraManager::SwitchToCurrent(const int32 InPlayerIndex, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCurrent(InPlayerIndex, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToCurrent(const int32 InPlayerIndex, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate& OnFinish)
{
	if (CurrentCameraTag.Contains(InPlayerIndex))
	{
		return SwitchToCamera(InPlayerIndex, CurrentCameraTag.FindRef(InPlayerIndex), SwitchCameraHandle, OnFinish);
	}

	OnFinish.ExecuteIfBound();
	return nullptr;
}

UCameraHandle* UCameraManager::SwitchToPrevious(const int32 InPlayerIndex, const TSubclassOf<UCameraHandle> InCameraHandleClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToPrevious(InPlayerIndex, NewObject<UCameraHandle>(this, InCameraHandleClass), OnFinish);
}

UCameraHandle* UCameraManager::SwitchToPrevious(const int32 InPlayerIndex, UCameraHandle* SwitchCameraHandle, const FSimpleDelegate& OnFinish)
{
	if (PreviousCameraTag.Contains(InPlayerIndex))
	{
		return SwitchToCamera(InPlayerIndex, PreviousCameraTag.FindRef(InPlayerIndex), SwitchCameraHandle, OnFinish);
	}

	OnFinish.ExecuteIfBound();
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

void UCameraManager::UpdateCameraTag(const int32 InPlayerIndex, const FGameplayTag InCameraTag)
{
	if (CurrentCameraTag.Contains(InPlayerIndex))
	{
		PreviousCameraTag.FindOrAdd(InPlayerIndex, CurrentCameraTag.FindRef(InPlayerIndex));
	}

	CurrentCameraTag.FindOrAdd(InPlayerIndex, InCameraTag);
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

	if (IsValid(CameraInputIdle) && CameraInputIdle->bEnableLensMovement)
	{
		OnCameraLensMovementStart.Broadcast(CameraInputIdle);
		CameraLensMovement = CameraInputIdle->LensMovementList[FMath::RandRange(0, CameraInputIdle->LensMovementList.Num() - 1)];
		CameraLensMovement->NativeStartLensMovement();
	}
}

bool UCameraManager::SetCameraInputIdle(UCameraInputIdle* InCameraInputIdle)
{
	if (UInputManager* InputManager = UManagerProxy::Get()->GetManager<UInputManager>())
	{
		if (IsValid(CameraInputIdle))
		{
			InputManager->UnRegisterIdleData(CameraInputIdle);
			CameraInputIdle = nullptr;
			OnCameraInputIdleReset.Broadcast(CameraInputIdle);
		}

		if (!IsValid(InCameraInputIdle) || InCameraInputIdle->AutoSwitchTags.IsEmpty() || !IsValid(InCameraInputIdle->CameraHandle) || InCameraInputIdle->TimeInterval < 0.f)
		{
			return false;
		}

		CameraInputIdle = InCameraInputIdle;
		InputManager->RegisterIdleData(CameraInputIdle, FInputIdleDelegate::CreateUObject(this, &UCameraManager::OnInputIdleStart), FInputIdleDelegate::CreateUObject(this, &UCameraManager::OnInputIdleStop));
		return true;
	}

	return false;
}

void UCameraManager::OnInputIdleStart(UInputIdle* InputIdle)
{
	if (CameraInputIdle == InputIdle)
	{
		if (CameraInputIdle->bEnableCameraAutoSwitch)
		{
			OnCameraAutoSwitchStart.Broadcast(CameraInputIdle);
			HandleCameraAutoSwitch();
		}

		if (CameraInputIdle->bEnableLensMovement)
		{
			HandleCameraLensMovement();
		}
	}
}

void UCameraManager::OnInputIdleStop(UInputIdle* InputIdle)
{
	/* 清理相机自动切换 */
	if (CameraInputIdle->bEnableCameraAutoSwitch)
	{
		if (IsValid(CameraInputIdle))
		{
			if (CameraInputIdle->bResetAutoSwitchIndex)
				CameraAutoSwitchIndex = 0;
		}

		GetWorld()->GetTimerManager().ClearTimer(AutoSwitchCameraHandle);
		OnCameraAutoSwitchStop.Broadcast(CameraInputIdle);
	}

	/* 清理相机运镜 */
	if (CameraInputIdle->bEnableLensMovement && IsValid(CameraLensMovement))
	{
		OnCameraLensMovementStop.Broadcast(CameraInputIdle);
		CameraLensMovement->NativeStopLensMovement();
		CameraLensMovement = nullptr;
	}
}

void UCameraManager::HandleCameraAutoSwitch()
{
	if (IsValid(CameraInputIdle))
	{
		/* 切回到第一个相机 */
		if (!CameraInputIdle->AutoSwitchTags.IsValidIndex(CameraAutoSwitchIndex))
		{
			CameraAutoSwitchIndex = 0;
		}

		/* 当前标签无效，跳过该相机 */
		if (!CameraInputIdle->AutoSwitchTags[CameraAutoSwitchIndex].IsValid())
		{
			CameraAutoSwitchIndex++;
			HandleCameraAutoSwitch();
			return;
		}

		float TimeInterval = CameraInputIdle->TimeInterval;

		if (CameraInputIdle->bIsTimerContainerHandleDuration)
			TimeInterval += CameraInputIdle->CameraHandle->GetSwitchDuration();

		GetWorld()->GetTimerManager().SetTimer(AutoSwitchCameraHandle, this, &UCameraManager::HandleCameraAutoSwitch, TimeInterval, false);

		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PC = Iterator->Get();
			SwitchToCamera(UGameplayStatics::GetPlayerControllerID(PC), CameraInputIdle->AutoSwitchTags[CameraAutoSwitchIndex], CameraInputIdle->CameraHandle);
			CameraAutoSwitchIndex++;
		}
	}
}

void UCameraManager::HandleCameraLensMovement()
{
	if (CameraInputIdle->bEnableCameraAutoSwitch)
	{
		/* 如果有相机的自动切换，在切换完成后处理相机运镜 */
		return;
	}
	else
	{
		OnCameraLensMovementStart.Broadcast(CameraInputIdle);
		CameraLensMovement = CameraInputIdle->LensMovementList[FMath::RandRange(0, CameraInputIdle->LensMovementList.Num() - 1)];
		CameraLensMovement->NativeStartLensMovement();
	}
}

#undef LOCTEXT_NAMESPACE
