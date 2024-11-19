// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonPawn.h"
#include "SmartCityPawn.generated.h"

UCLASS()
class DEVGAMEPLAY_API ASmartCityPawn : public AThirdPersonPawn
{
	GENERATED_BODY()

public:
	ASmartCityPawn(const FObjectInitializer& ObjectInitializer);

	/* IPawnInputMovementInterface */
public:
	virtual bool ReassessmentTargetArmLength_Implementation() override;
};
