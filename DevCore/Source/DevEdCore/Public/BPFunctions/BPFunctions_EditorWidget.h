// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_EditorWidget.generated.h"

class SLevelViewport;

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBPFunctions_EditorWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool CurrentEditorProjectWorldToScreen(const FVector& WorldPosition, FVector2D& ScreenPosition);
	static bool GetCurrentEditorProjectionData(FSceneViewProjectionData& ProjectionData);
	
	static bool EditorProjectWorldToScreen(const FLevelEditorViewportClient* InLevelEditorViewportClient, const FVector& WorldPosition, FVector2D& ScreenPosition);
	static bool GetEditorProjectionData(const FLevelEditorViewportClient* InLevelEditorViewportClient, FSceneViewProjectionData& ProjectionData);

public:
	static TSharedPtr<SLevelViewport> GetEditorViewportWidget(const FLevelEditorViewportClient* InLevelEditorViewportClient);
	static bool AddToEditorViewport(const FLevelEditorViewportClient* InLevelEditorViewportClient, const TSharedRef<SWidget>& InWidget);
	static bool RemoveFromEditorViewport(const FLevelEditorViewportClient* InLevelEditorViewportClient, const TSharedRef<SWidget>& InWidget);
};
