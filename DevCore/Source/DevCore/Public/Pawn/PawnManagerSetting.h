// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "PawnManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UPawnManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, ClampMax = 10.f))
	float MovementSpeed = 1.f;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.1f, ClampMax = 10.f))
	float RotationSpeed = 1.f;

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0.f, UIMin = 0.f))
	float RefreshSpringArmLengthThreshold = 200.f;
};
