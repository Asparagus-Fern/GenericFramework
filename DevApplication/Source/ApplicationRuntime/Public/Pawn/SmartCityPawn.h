// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/DevPawn.h"
#include "SmartCityPawn.generated.h"

class UCameraHandle;

UCLASS()
class APPLICATIONRUNTIME_API ASmartCityPawn : public ADevPawn
{
	GENERATED_BODY()

public:
	ASmartCityPawn();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	UCameraComponent* DuplicateCameraComponent = nullptr;

protected:
	virtual UCameraComponent* GetActiveCameraComponent_Implementation() override;
	virtual void OnSwitchCameraBegin(UCameraHandle* InCameraHandle);
	virtual void OnSwitchCameraFinish(UCameraHandle* InCameraHandle);
};
