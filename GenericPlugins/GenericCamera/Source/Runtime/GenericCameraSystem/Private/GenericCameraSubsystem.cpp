// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericCameraSubsystem.h"

#include "CameraType.h"
#include "CineCameraComponent.h"
#include "Camera/CameraActor.h"
#include "CameraPoint/GenericCameraPoint.h"
#include "CameraPoint/CameraPointBase.h"
#include "CameraPoint/GenericCineCameraPoint.h"
#include "CameraSwitch/GenericCameraSwitchMethod.h"
#include "Kismet/GameplayStatics.h"
#include "Type/GenericType.h"

#define LOCTEXT_NAMESPACE "FGenericCameraSystemModule"

UGenericCameraSubsystem* UGenericCameraSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UGenericCameraSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ACameraPointBase::OnCameraPointRegister.AddUObject(this, &UGenericCameraSubsystem::AddCameraPoint);
	ACameraPointBase::OnCameraPointUnRegister.AddUObject(this, &UGenericCameraSubsystem::RemoveCameraPoint);
	UGenericCameraSwitchMethod::OnSwitchCameraFinish.AddUObject(this, &UGenericCameraSubsystem::HandleSwitchToCameraFinish);
}

void UGenericCameraSubsystem::Deinitialize()
{
	Super::Deinitialize();
	ACameraPointBase::OnCameraPointRegister.RemoveAll(this);
	ACameraPointBase::OnCameraPointUnRegister.RemoveAll(this);
	UGenericCameraSwitchMethod::OnSwitchCameraFinish.RemoveAll(this);
}

void UGenericCameraSubsystem::AddCameraPoint(ACameraPointBase* InCameraPoint)
{
	if (IsValid(InCameraPoint) && InCameraPoint->CameraTag.IsValid() && !CameraPoints.Contains(InCameraPoint->CameraTag))
	{
		CameraPoints.FindOrAdd(InCameraPoint->CameraTag, InCameraPoint);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraPointRegister, BPDelegate_OnCameraPointRegister, InCameraPoint)
	}
}

void UGenericCameraSubsystem::RemoveCameraPoint(ACameraPointBase* InCameraPoint)
{
	if (IsValid(InCameraPoint) && InCameraPoint->CameraTag.IsValid() && CameraPoints.Contains(InCameraPoint->CameraTag))
	{
		CameraPoints.Remove(InCameraPoint->CameraTag);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraPointUnRegister, BPDelegate_OnCameraPointUnRegister, InCameraPoint)
	}
}

void UGenericCameraSubsystem::HandleSwitchToCameraFinish(UGenericCameraSwitchMethod* InCameraHandle)
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

bool UGenericCameraSubsystem::CanSwitchToCamera(const FGameplayTag InCameraTag) const
{
	return InCameraTag.IsValid() && IsValid(GetCameraPoint(InCameraTag));
}

ACameraPointBase* UGenericCameraSubsystem::GetCameraPoint(const FGameplayTag InCameraTag) const
{
	if (CameraPoints.Contains(InCameraTag))
	{
		return CameraPoints.FindRef(InCameraTag);
	}

	return nullptr;
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, const FVector& Location, const FRotator& Rotation, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, Location, Rotation, NewObject<UGenericCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, const FVector& Location, const FRotator& Rotation, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	AGenericCameraPoint* SpawnCameraPoint = GetWorld()->SpawnActor<AGenericCameraPoint>(Location, Rotation);
	return SwitchToCamera(InPlayer, SpawnCameraPoint, InSwitchCameraMethod, OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, const ACameraActor* InCameraActor, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, InCameraActor->GetCameraComponent(), InCameraMethodClass, OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, const ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, InCameraActor->GetCameraComponent(), InSwitchCameraMethod, OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, UCameraComponent* InCameraComponent, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, InCameraComponent, NewObject<UGenericCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	ACameraPointBase* SpawnCameraPoint;
	if (InCameraComponent->IsA(UCineCameraComponent::StaticClass()))
	{
		SpawnCameraPoint = GetWorld()->SpawnActor<AGenericCineCameraPoint>(InCameraComponent->GetComponentLocation(), InCameraComponent->GetComponentRotation());
	}
	else
	{
		SpawnCameraPoint = GetWorld()->SpawnActor<AGenericCameraPoint>(InCameraComponent->GetComponentLocation(), InCameraComponent->GetComponentRotation());
	}

	SpawnCameraPoint->SetCameraComponent(InCameraComponent);
	return SwitchToCamera(InPlayer, SpawnCameraPoint, InSwitchCameraMethod, OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, const FGameplayTag InCameraTag, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, InCameraTag, NewObject<UGenericCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, const FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, GetCameraPoint(InCameraTag), InSwitchCameraMethod, OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, ACameraPointBase* InCameraPoint, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCamera(InPlayer, InCameraPoint, NewObject<UGenericCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCamera(APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("Player Is InValid"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	if (!IsValid(InCameraPoint))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("CameraPoint Is InValid"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	if (!IsValid(InSwitchCameraMethod))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("SwitchCameraMethod Is InValid"))
		OnFinish.ExecuteIfBound();
		return nullptr;
	}

	/* Reset Current Switching Camera */
	if (IsSwitching(InPlayer))
	{
		UGenericCameraSwitchMethod* CameraHandle = GetCameraSwitchMethod(InPlayer);
		CameraHandle->NativeOnSwitchToCameraPointReset();
	}

	CurrentCameraMethods.AddUnique(InSwitchCameraMethod);

	/* Record The Previous And Current Camera Tag */
	if (InCameraPoint->CameraTag.IsValid())
	{
		UpdateCameraTag(InPlayer, InCameraPoint->CameraTag);
	}

	InSwitchCameraMethod->NativeHandleSwitchToCameraPoint(InPlayer, InCameraPoint, OnFinish);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnCameraSwitchBegin, BPDelegate_OnCameraSwitchBegin, InCameraPoint, InSwitchCameraMethod);

	return InSwitchCameraMethod;
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCurrent(APlayerController* InPlayer, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToCurrent(InPlayer, NewObject<UGenericCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToCurrent(APlayerController* InPlayer, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	if (CurrentCameraTag.Contains(InPlayer))
	{
		return SwitchToCamera(InPlayer, CurrentCameraTag.FindRef(InPlayer), InSwitchCameraMethod, OnFinish);
	}

	OnFinish.ExecuteIfBound();
	return nullptr;
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToPrevious(APlayerController* InPlayer, const TSubclassOf<UGenericCameraSwitchMethod>& InCameraMethodClass, const FSimpleDelegate& OnFinish)
{
	return SwitchToPrevious(InPlayer, NewObject<UGenericCameraSwitchMethod>(this, InCameraMethodClass), OnFinish);
}

UGenericCameraSwitchMethod* UGenericCameraSubsystem::SwitchToPrevious(APlayerController* InPlayer, UGenericCameraSwitchMethod* InSwitchCameraMethod, const FSimpleDelegate& OnFinish)
{
	if (PreviousCameraTag.Contains(InPlayer))
	{
		return SwitchToCamera(InPlayer, PreviousCameraTag.FindRef(InPlayer), InSwitchCameraMethod, OnFinish);
	}

	OnFinish.ExecuteIfBound();
	return nullptr;
}

bool UGenericCameraSubsystem::IsSwitching(const APlayerController* InPlayerController)
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

UGenericCameraSwitchMethod* UGenericCameraSubsystem::GetCameraSwitchMethod(const APlayerController* InPlayerController)
{
	for (const auto& Method : CurrentCameraMethods)
	{
		if (Method->OwnerPlayerController == InPlayerController)
		{
			return Method;
		}
	}
	return nullptr;
}

void UGenericCameraSubsystem::UpdateCameraTag(APlayerController* InPlayer, const FGameplayTag InCameraTag)
{
	if (CurrentCameraTag.Contains(InPlayer))
	{
		PreviousCameraTag.FindOrAdd(InPlayer, CurrentCameraTag.FindRef(InPlayer));
	}

	CurrentCameraTag.FindOrAdd(InPlayer, InCameraTag);
}

#undef LOCTEXT_NAMESPACE
