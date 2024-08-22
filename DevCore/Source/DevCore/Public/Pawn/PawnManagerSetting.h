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
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.1f, ClampMax = 10.f))
	float MovementSpeed = 1.f;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.1f, ClampMax = 10.f))
	float RotationSpeed = 1.f;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = -89.99f, ClampMax = 0.f))
	float MinRotationPitch = -89.9f;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(ClampMin = -89.99f, ClampMax = 0.f))
	float MaxRotationPitch = 0.f;
};
