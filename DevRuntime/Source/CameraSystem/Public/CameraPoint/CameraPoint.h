// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPointBase.h"
#include "GameFramework/Actor.h"
#include "CameraPoint.generated.h"

class UCameraHandle;
class UCameraComponent;

UCLASS()
class CAMERASYSTEM_API ACameraPoint : public ACameraPointBase
{
	GENERATED_BODY()

public:
	ACameraPoint();
	virtual UCameraComponent* GetCameraComponent_Implementation() override;
	virtual void SetCameraComponent_Implementation(UCameraComponent* InCameraComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Point")
	UCameraComponent* CameraComponent = nullptr;
};
