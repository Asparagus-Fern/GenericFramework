// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraEdManager.h"

#include "CameraSystemType.h"
#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"
#include "CameraPoint/CameraPointBase.h"

#define LOCTEXT_NAMESPACE "UCameraEdManager"

UCameraEdManager::UCameraEdManager()
{
}

bool UCameraEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
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

	FCameraSystemDelegates::OnCopyViewportCamera.RemoveAll(this);
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.RemoveAll(this);
}

void UCameraEdManager::OnCopyViewportCamera(ACameraPointBase* InCameraPoint)
{
	if (!IsValid(GetWorld()))
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
