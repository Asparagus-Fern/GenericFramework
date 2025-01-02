// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraEdManager.h"

#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"
#include "CameraPoint/CameraPointBase.h"

#define LOCTEXT_NAMESPACE "UCameraEdManager"

bool UCameraEdManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UCameraEdManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ACameraPointBase::OnCopyViewportCamera.AddUObject(this, &UCameraEdManager::OnCopyViewportCamera);
	ACameraPointBase::OnCameraPointPilotStateChanged.AddUObject(this, &UCameraEdManager::OnCameraPointPilotStateChanged);
}

void UCameraEdManager::Deinitialize()
{
	Super::Deinitialize();

	ACameraPointBase::OnCopyViewportCamera.RemoveAll(this);
	ACameraPointBase::OnCameraPointPilotStateChanged.RemoveAll(this);
}

bool UCameraEdManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

void UCameraEdManager::OnCopyViewportCamera(ACameraPointBase* InCameraPoint)
{
	InCameraPoint->Modify();
	InCameraPoint->SetActorLocation(GCurrentLevelEditingViewportClient->GetViewLocation());
	InCameraPoint->SetActorRotation(GCurrentLevelEditingViewportClient->GetViewRotation());

	GEditor->RedrawLevelEditingViewports();
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
