// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPointBase.h"
#include "GameFramework/Actor.h"
#include "CameraPoint.generated.h"

class UCameraSwitchMethod;
class UCameraComponent;

UCLASS()
class CAMERASYSTEM_API ACameraPoint : public ACameraPointBase
{
	GENERATED_BODY()

public:
	ACameraPoint(const FObjectInitializer& ObjectInitializer);

	/* ACameraPointBase */
public:
	virtual UCameraComponent* GetCameraComponent_Implementation() override;
	virtual void SetCameraComponent_Implementation(UCameraComponent* InCameraComponent) override;

	/* ACameraPoint */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;
};
