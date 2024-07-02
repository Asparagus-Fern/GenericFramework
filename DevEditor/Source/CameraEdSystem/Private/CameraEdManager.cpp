// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraEdManager.h"

#include "CameraSystemType.h"
#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"
#include "CameraPoint/CameraPointBase.h"
#include "Manager/ManagerEdGlobal.h"

#define LOCTEXT_NAMESPACE "UCameraEdManager"

UCameraEdManager::UCameraEdManager()
{
}

void UCameraEdManager::NativeOnCreate()
{
	Super::NativeOnCreate();

	FCameraSystemDelegates::OnCopyViewportCamera.AddUObject(this, &UCameraEdManager::OnCopyViewportCamera);
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.AddUObject(this, &UCameraEdManager::OnCameraPointPilotStateChanged);
}

void UCameraEdManager::NativeOnDestroy()
{
	Super::NativeOnDestroy();
}

void UCameraEdManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UCameraEdManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

FText UCameraEdManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Camera Editor Manager");
}

bool UCameraEdManager::DoesSupportWorldType(EWorldType::Type InWorldType)
{
	return Super::DoesSupportWorldType(InWorldType) || InWorldType == EWorldType::Editor;
}

void UCameraEdManager::OnCopyViewportCamera(ACameraPointBase* InCameraPoint)
{
	if (!IsValid(GetWorld()) && IsValid(FManagerEdGlobal::GetEditorWorld()))
	{
		InCameraPoint->Modify();
		InCameraPoint->SetActorLocation(GCurrentLevelEditingViewportClient->GetViewLocation());
		InCameraPoint->SetActorRotation(GCurrentLevelEditingViewportClient->GetViewRotation());

		GEditor->RedrawLevelEditingViewports();
	}
}

void UCameraEdManager::OnCameraPointPilotStateChanged(ACameraPointBase* InCameraPoint, bool bIsPilot)
{
	ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	if (bIsPilot)
	{
		LevelEditorSubsystem->PilotLevelActor(InCameraPoint);
	}
	else
	{
		LevelEditorSubsystem->EjectPilotLevelActor();
	}
}

#undef LOCTEXT_NAMESPACE
