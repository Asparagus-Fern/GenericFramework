// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCaptureTool.h"

#include "Editor.h"
#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"
#include "Camera/CameraComponent.h"
#include "Slate/SceneViewport.h"

AMapCaptureTool::AMapCaptureTool()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Capture");
	CameraComponent->SetupAttachment(SceneComponent);
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	CameraComponent->SetOrthoWidth(512.f);
	CameraComponent->SetConstraintAspectRatio(true);
	CameraComponent->SetAspectRatio(1.f);

	SetActorRotation(FRotator(-90.f, 0.f, 0.f));
}

#if WITH_EDITOR

void AMapCaptureTool::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AMapCaptureTool::CaptureMap()
{
	if (CanCapture())
	{
		ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
		LevelEditorSubsystem->PilotLevelActor(this);
		GCurrentLevelEditingViewportClient->SetViewMode(VMI_Lit);

		SetActorLocation(FVector(CaptureOrigin.X + CurrentRow * GetOrthoWidth() + GetHalfOrthoWidth(), CaptureOrigin.Y + CurrentColumn * GetOrthoWidth() + GetHalfOrthoWidth(), CaptureOrigin.Z));

		if (FViewport* Viewport = GCurrentLevelEditingViewportClient->Viewport)
		{
			if (FSceneViewport* SceneViewport = StaticCast<FSceneViewport*>(Viewport))
			{
				SceneViewport->TakeHighResScreenShot();
			}
		}

		CurrentRow++;
		if (CurrentRow == Row)
		{
			CurrentRow = 0;
			CurrentColumn++;
		}

		if (CurrentColumn == Column)
		{
			CurrentRow = 0;
			CurrentColumn = 0;

			GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([LevelEditorSubsystem]()
					{
						LevelEditorSubsystem->EjectPilotLevelActor();
					}
				)
			);
		}
		else
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUFunction(this, "CaptureMap"), 1.f, false);
			// GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUFunction(this, "CaptureMap"));
		}
	}
}

#endif
