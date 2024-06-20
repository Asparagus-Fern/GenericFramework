// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonPawn.h"
#include "SmartCityPawn.generated.h"

class ACameraPoint;

UCLASS()
class APPLICATIONRUNTIME_API ASmartCityPawn : public AThirdPersonPawn
{
	GENERATED_BODY()

public:
	ASmartCityPawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
