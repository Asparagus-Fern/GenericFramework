// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraPointBase.h"
#include "GameFramework/Actor.h"
#include "CameraPoint.generated.h"

class UCameraSwitchMethod;
class UCameraComponent;

UCLASS(MinimalAPI)
class ACameraPoint : public ACameraPointBase
{
	GENERATED_BODY()

public:
	ACameraPoint(const FObjectInitializer& ObjectInitializer);

	/* ACameraPointBase */
public:
	CAMERASYSTEM_API virtual UCameraComponent* GetCameraComponent_Implementation() override;
	CAMERASYSTEM_API virtual void SetCameraComponent_Implementation(UCameraComponent* InCameraComponent) override;

	/* ACameraPoint */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;
};
