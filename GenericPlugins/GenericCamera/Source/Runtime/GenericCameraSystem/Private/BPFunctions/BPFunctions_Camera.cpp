// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_Camera.h"

#include "GenericCameraSubsystem.h"

ACameraPointBase* UBPFunctions_Camera::GetCameraPoint(const UObject* WorldContextObject, const FGameplayTag InCameraTag)
{
	if (const UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		return GenericCameraSubsystem->GetCameraPoint(InCameraTag);
	}

	return nullptr;
}

void UBPFunctions_Camera::SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, FVector Location, FRotator Rotation, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, Location, Rotation, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, FVector Location, FRotator Rotation, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, Location, Rotation, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Actor_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraActor, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraActor, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Component_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraComponent, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Component_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraComponent, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Tag_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, const FGameplayTag InCameraTag, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraTag, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, const FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraTag, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_CameraPoint_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraPoint, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraPoint, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCurrent_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCurrent(InPlayer, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCurrent_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCurrent(InPlayer, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToPrevious_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToPrevious(InPlayer, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToPrevious_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle)
{
	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToPrevious(InPlayer, InCameraHandle);
	}
}
