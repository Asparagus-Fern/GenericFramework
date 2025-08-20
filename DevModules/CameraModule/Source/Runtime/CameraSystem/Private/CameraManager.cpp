// Copyright ChenTaiye 2025. All Rights Reserved.


#include "CameraManager.h"

#include "CameraType.h"
#include "CineCameraComponent.h"
#include "Camera/CameraActor.h"
#include "CameraPoint/CameraPoint.h"
#include "CameraPoint/CameraPointBase.h"
#include "CameraPoint/CineCameraPoint.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerProxy.h"

#define LOCTEXT_NAMESPACE "FCameraSystemModule"

bool UCameraManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UCameraManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	ACameraPointBase::OnCameraPointRegister.AddUObject(this, &UCameraManager::AddCameraPoint);
	ACameraPointBase::OnCameraPointUnRegister.AddUObject(this, &UCameraManager::RemoveCameraPoint);
	UCameraSwitchMethod::OnSwitchCameraFinish.AddUObject(this, &UCameraManager::HandleSwitchToCameraFinish);
}

void UCameraManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	ACameraPointBase::OnCameraPointRegister.RemoveAll(this);
	ACameraPointBase::OnCameraPointUnRegister.RemoveAll(this);
	UCameraSwitchMethod::OnSwitchCameraFinish.RemoveAll(this);
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
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraPointRegister, BPDelegate_OnCameraPointRegister, InCameraPoint)
	}
}

void UCameraManager::RemoveCameraPoint(ACameraPointBase* InCameraPoint)
{
	if (IsValid(InCameraPoint) && InCameraPoint->CameraTag.IsValid() && CameraPoints.Contains(InCameraPoint->CameraTag))
	{
		CameraPoints.Remove(InCameraPoint->CameraTag);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraPointUnRegister, BPDelegate_OnCameraPointUnRegister, InCameraPoint)
	}
}

void UCameraManager::HandleSwitchToCameraFinish(UCameraSwitchMethod* InCameraHandle)
{
	if (!IsValid(InCameraHandle))
	{
		return;
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraSwitchEnd, BPDelegate_OnCameraSwitchEnd, InCameraHandle->TargetCameraPoint, InCameraHandle);

	if (CurrentCameraMethods.Contains(InCameraHandle))
	{
		CurrentCameraMethods.Remove(InCameraHandle);
	}
	
}

bool UCameraManager::CanSwitchToCamera(const FGameplayTag InCameraTag) const
{
	return InCameraTag.IsValid() && IsValid(GetCameraPoint(InCameraTag));
}

ACameraPointBase* UCameraManager::GetCameraPoint(const FGameplayTag InCameraTag) const
{
	if (CameraPoints.Contains(InCameraTag))
	{
		return CameraPoints.FindRef(InCameraTag);
	}

	return nullptr;
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraMethodClass)
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, Location, Rotation, NewObject<UCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InSwitchCameraMethod))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	ACameraPoint* SpawnCameraPoint = GetWorld()->SpawnActor<ACameraPoint>(Location, Rotation);
	return SwitchToCamera(InPlayerIndex, SpawnCameraPoint, InSwitchCameraMethod, OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraActor || !InCameraMethodClass)
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraActor->GetCameraComponent(), InCameraMethodClass, OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate OnFinish)
{
	if (!InCameraActor || !IsValid(InSwitchCameraMethod))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraActor->GetCameraComponent(), InSwitchCameraMethod, OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraComponent) || !InCameraMethodClass)
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraComponent, NewObject<UCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraComponent) || !IsValid(InSwitchCameraMethod))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
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
	return SwitchToCamera(InPlayerIndex, SpawnCameraPoint, InSwitchCameraMethod, OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FGameplayTag InCameraTag, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate OnFinish)
{
	if (!InCameraTag.IsValid() || !InCameraMethodClass)
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}


	return SwitchToCamera(InPlayerIndex, InCameraTag, NewObject<UCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, const FGameplayTag InCameraTag, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate OnFinish)
{
	if (!InCameraTag.IsValid() || !IsValid(InSwitchCameraMethod) || !IsValid(GetCameraPoint(InCameraTag)))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, GetCameraPoint(InCameraTag), InSwitchCameraMethod, OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraPoint) || !InCameraMethodClass)
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	return SwitchToCamera(InPlayerIndex, InCameraPoint, NewObject<UCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCamera(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate OnFinish)
{
	if (!IsValid(InCameraPoint) || !IsValid(InSwitchCameraMethod))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchToCamera Fail"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(InCameraPoint, InPlayerIndex))
	{
		if (IsSwitching(PC))
		{
			UCameraSwitchMethod* CameraHandle = GetCameraHandle(PC);
			CameraHandle->NativeOnSwitchToCameraPointReset();
		}

		CurrentCameraMethods.AddUnique(InSwitchCameraMethod);

		if (InCameraPoint->CameraTag.IsValid())
		{
			UpdateCameraTag(InPlayerIndex, InCameraPoint->CameraTag);
		}

		InSwitchCameraMethod->NativeHandleSwitchToCameraPoint(PC, InCameraPoint, OnFinish);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraSwitchBegin, BPDelegate_OnCameraSwitchBegin, InCameraPoint, InSwitchCameraMethod);

		return InSwitchCameraMethod;
	}

	return nullptr;
}

UCameraSwitchMethod* UCameraManager::SwitchToCurrent(const int32 InPlayerIndex, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCurrent(InPlayerIndex, NewObject<UCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToCurrent(const int32 InPlayerIndex, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	if (CurrentCameraTag.Contains(InPlayerIndex))
	{
		return SwitchToCamera(InPlayerIndex, CurrentCameraTag.FindRef(InPlayerIndex), InSwitchCameraMethod, OnFinish);
	}

	OnFinish.ExecuteIfBound();
	return nullptr;
}

UCameraSwitchMethod* UCameraManager::SwitchToPrevious(const int32 InPlayerIndex, const TSubclassOf<UCameraSwitchMethod> InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToPrevious(InPlayerIndex, NewObject<UCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UCameraSwitchMethod* UCameraManager::SwitchToPrevious(const int32 InPlayerIndex, UCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	if (PreviousCameraTag.Contains(InPlayerIndex))
	{
		return SwitchToCamera(InPlayerIndex, PreviousCameraTag.FindRef(InPlayerIndex), InSwitchCameraMethod, OnFinish);
	}

	OnFinish.ExecuteIfBound();
	return nullptr;
}

bool UCameraManager::IsSwitching(const APlayerController* InPlayerController)
{
	ensure(InPlayerController);

	if (IsValid(InPlayerController))
	{
		for (const auto& CurrentCameraHandle : CurrentCameraMethods)
		{
			if (CurrentCameraHandle->OwnerPlayerController == InPlayerController)
			{
				return true;
			}
		}
	}

	return false;
}

UCameraSwitchMethod* UCameraManager::GetCameraHandle(const APlayerController* InPlayerController)
{
	for (const auto& CurrentCameraHandle : CurrentCameraMethods)
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

#undef LOCTEXT_NAMESPACE
