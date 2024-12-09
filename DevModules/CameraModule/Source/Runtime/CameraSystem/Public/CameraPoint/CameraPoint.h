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

	/* ACameraPointBase */
public:
	virtual UCameraComponent* GetCameraComponent_Implementation() override;

protected:
	virtual void SetCameraComponentInternal(UCameraComponent* InCameraComponent) override;

	/* ACameraPoint */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Point")
	UCameraComponent* CameraComponent = nullptr;
};
