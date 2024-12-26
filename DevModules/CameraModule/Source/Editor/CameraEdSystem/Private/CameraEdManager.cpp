// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraEdManager.h"

#include "CameraEdManagerSetting.h"
#include "LevelEditor.h"
#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"
#include "SLevelViewport.h"
#include "BPFunctions/BPFunctions_EditorWidget.h"
#include "CameraPoint/CameraPointBase.h"
#include "Slate/SceneViewport.h"

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

/*void UCameraEdManager::OnCameraViewportCapture(ACameraPointBase* InCameraPoint)
{
	for (auto& ViewportClient : GEditor->GetLevelViewportClients())
	{
		FLevelViewportActorLock& ActorLock = ViewportClient->GetActorLock();
		if (ActorLock.GetLockedActor() == InCameraPoint)
		{
			// TSharedPtr<SLevelViewport> LevelViewport = UBPFunctions_EditorWidget::GetEditorViewportWidget(ViewportClient);
			// TSharedPtr<FSceneViewport> SceneViewport = LevelViewport->GetSceneViewport();
			// if (SceneViewport.IsValid())
			// {
			// 	GScreenshotResolutionX = InCameraPoint->GetCameraComponent()->OrthoWidth * InCameraPoint->GetCameraComponent()->AspectRatio;
			// 	GScreenshotResolutionY = InCameraPoint->GetCameraComponent()->OrthoWidth;
			// }

			// SceneViewport->TakeHighResScreenShot();

			FScreenshotRequest::RequestScreenshot(false);
			ViewportClient->ProcessScreenShots(ViewportClient->Viewport);

			break;
		}
	}
}*/

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
