// Copyright ChenTaiye 2025. All Rights Reserved.

#include "AsyncAction/SwitchToCameraAsyncAction.h"

#include "GenericCameraSubsystem.h"

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::FocusToActor_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, AActor* InActor, float FocusLens, TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->FocusToActor(InPlayer, InActor, FocusLens, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::FocusToActor_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, AActor* InActor, float FocusLens, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->FocusToActor(InPlayer, InActor, FocusLens, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, APlayerController* InPlayer, const FVector Location, const FRotator Rotation, const TSubclassOf<UGenericCameraSwitchMethod> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, Location, Rotation, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, const FVector Location, const FRotator Rotation, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, Location, Rotation, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
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

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraActor* InCameraActor, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraActor, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
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

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Component_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UCameraComponent* InCameraComponent, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraComponent, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
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

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, const FGameplayTag InCameraTag, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraTag, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
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

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, ACameraPointBase* InCameraPoint, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCamera(InPlayer, InCameraPoint, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
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

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCurrent_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToCurrent(InPlayer, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
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

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToPrevious_Handle(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericCameraSwitchMethod* InCameraSwitchMethod)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UGenericCameraSubsystem* GenericCameraSubsystem = UGenericCameraSubsystem::Get(WorldContextObject))
	{
		GenericCameraSubsystem->SwitchToPrevious(InPlayer, InCameraSwitchMethod, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void USwitchToCameraAsyncAction::OnHandleFinish()
{
	OnFinish.Broadcast();
}
