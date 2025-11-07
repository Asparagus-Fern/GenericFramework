// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraPointBase.h"
#include "GenericCineCameraPoint.generated.h"

class UCineCameraComponent;

UCLASS(MinimalAPI)
class AGenericCineCameraPoint : public ACameraPointBase
{
	GENERATED_BODY()

public:
	AGenericCineCameraPoint(const FObjectInitializer& ObjectInitializer);

	/* ACameraPointBase */
public:
	GENERICCAMERASYSTEM_API virtual UCameraComponent* GetCameraComponent_Implementation() override;
	GENERICCAMERASYSTEM_API virtual void SetCameraComponent_Implementation(UCameraComponent* InCameraComponent) override;

	/* ACineCameraPoint */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCineCameraComponent* CineCameraComponent = nullptr;
};
