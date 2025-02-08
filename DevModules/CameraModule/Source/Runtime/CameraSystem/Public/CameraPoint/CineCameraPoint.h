// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPointBase.h"
#include "CineCameraPoint.generated.h"

class UCineCameraComponent;

UCLASS()
class CAMERASYSTEM_API ACineCameraPoint : public ACameraPointBase
{
	GENERATED_BODY()

public:
	ACineCameraPoint(const FObjectInitializer& ObjectInitializer);

	/* ACameraPointBase */
public:
	virtual UCameraComponent* GetCameraComponent_Implementation() override;
	virtual void SetCameraComponent_Implementation(UCameraComponent* InCameraComponent) override;

	/* ACineCameraPoint */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCineCameraComponent* CineCameraComponent = nullptr;
};
