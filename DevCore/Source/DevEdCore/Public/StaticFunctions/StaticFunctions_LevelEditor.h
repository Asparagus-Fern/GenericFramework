// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SLevelViewport;

/**
 * 
 */
class DEVEDCORE_API FStaticFunctions_LevelEditor
{
	/* World Location To Screen Position */
public:
	static bool CurrentEditorProjectWorldToScreen(const FVector& WorldPosition, FVector2D& ScreenPosition);
	static bool EditorProjectWorldToScreen(FLevelEditorViewportClient* InLevelEditorViewportClient, const FVector& WorldPosition, FVector2D& ScreenPosition);

	static bool GetCurrentEditorProjectionData(FSceneViewProjectionData& ProjectionData);
	static bool GetEditorProjectionData(FLevelEditorViewportClient* InLevelEditorViewportClient, FSceneViewProjectionData& ProjectionData);

	/* Level Editor Viewport Widget */
public:
	static TSharedPtr<SLevelViewport> GetEditorViewportWidget(const FLevelEditorViewportClient* InLevelEditorViewportClient);
	static void AddToViewport(const FLevelEditorViewportClient* InLevelEditorViewportClient, const TSharedRef<SWidget>& InWidget);
	static void RemoveFromViewport(const FLevelEditorViewportClient* InLevelEditorViewportClient, const TSharedRef<SWidget>& InWidget);
};
