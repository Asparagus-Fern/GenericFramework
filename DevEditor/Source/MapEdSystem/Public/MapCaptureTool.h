// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "MapCaptureTool.generated.h"

class UCameraComponent;

UCLASS()
class MAPEDSYSTEM_API AMapCaptureTool : public AActor
{
	GENERATED_BODY()

public:
	AMapCaptureTool();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector CaptureOrigin = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Row = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Column = 0;

public:
	UFUNCTION(CallInEditor, BlueprintCallable, Category="MapCaptureTool")
	void CaptureMap();

protected:
	int32 CurrentRow = 0;
	int32 CurrentColumn = 0;
	bool CanCapture() const { return CurrentRow < Row && CurrentColumn < Column; }
	float GetOrthoWidth() const { return CameraComponent->OrthoWidth; }
	float GetHalfOrthoWidth() const { return CameraComponent->OrthoWidth / 2; }
};
