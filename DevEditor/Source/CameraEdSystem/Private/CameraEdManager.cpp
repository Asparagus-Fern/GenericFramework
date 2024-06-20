// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraEdManager.h"

#include "CameraPoint.h"
#include "CameraSystemType.h"
#include "LevelEditor.h"
#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"

#define LOCTEXT_NAMESPACE "UCameraEdManager"

UCameraEdManager::UCameraEdManager()
{
	DisplayName = LOCTEXT("DisplayName", "Camera Editor Manager");
	ProcedureOrder = 0;
}

void UCameraEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCameraSystemDelegates::OnCopyViewportCamera.AddUObject(this, &UCameraEdManager::OnCopyViewportCamera);
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.AddUObject(this, &UCameraEdManager::OnCameraPointPilotStateChanged);
}

void UCameraEdManager::Deinitialize()
{
	Super::Deinitialize();
}

void UCameraEdManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UCameraEdManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

void UCameraEdManager::OnCopyViewportCamera(ACameraPoint* InCameraPoint)
{
	if (GetWorld()->WorldType == EWorldType::Editor)
	{
		InCameraPoint->Modify();
		InCameraPoint->SetActorLocation(GCurrentLevelEditingViewportClient->GetViewLocation());
		InCameraPoint->SetActorRotation(GCurrentLevelEditingViewportClient->GetViewRotation());

		GEditor->RedrawLevelEditingViewports();
	}
}

void UCameraEdManager::OnCameraPointPilotStateChanged(ACameraPoint* InCameraPoint, bool bIsPilot)
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
