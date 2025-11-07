// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/SwitchToCameraAsyncAction.h"

#include "GenericCameraSubsystem.h"

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, const FVector Location, const FRotator Rotation, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, Location, Rotation, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, const FVector Location, const FRotator Rotation, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, Location, Rotation, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Actor_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraActor, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraActor, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Component_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraComponent, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Component_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraComponent, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Tag_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, const FGameplayTag InCameraTag, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraTag, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, const FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraTag, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_CameraPoint_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraPoint, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraPoint, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCurrent_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCurrent(InPlayer, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCurrent_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCurrent(InPlayer, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToPrevious_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToPrevious(InPlayer, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToPrevious_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToPrevious(InPlayer, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void USwitchToCameraAsyncAction::OnHandleFinish()
{
	OnFinish.Broadcast();
}
