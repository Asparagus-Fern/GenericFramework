// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraPointBase.h"
#include "GameFramework/Actor.h"
#include "GenericCameraPoint.generated.h"

class UGenericCameraSwitchMethod;
class UCameraComponent;

UCLASS(MinimalAPI)
class AGenericCameraPoint : public ACameraPointBase
{
	GENERATED_BODY()

public:
	AGenericCameraPoint(const FObjectInitializer& ObjectInitializer);

	/* ACameraPointBase */
public:
	GENERICCAMERASYSTEM_API virtual UCameraComponent* GetCameraComponent_Implementation() override;
	GENERICCAMERASYSTEM_API virtual void SetCameraComponent_Implementation(UCameraComponent* InCameraComponent) override;

	/* ACameraPoint */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* CameraComponent = nullptr;
};
