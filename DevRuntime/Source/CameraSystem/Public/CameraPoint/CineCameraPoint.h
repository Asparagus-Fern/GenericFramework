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
	ACineCameraPoint();
	virtual UCameraComponent* GetCameraComponent_Implementation() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Point")
	UCineCameraComponent* CineCameraComponent = nullptr;
};
