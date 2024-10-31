// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonPawn.h"
#include "SmartCityPawn.generated.h"

UCLASS()
class APPLICATIONRUNTIME_API ASmartCityPawn : public AThirdPersonPawn
{
	GENERATED_BODY()

public:
	ASmartCityPawn();
	virtual void AddZoom_Implementation(float InValue) override;

protected:
	/* 是否重新评估Pawn的位置和弹簧臂长度 */
	bool bEnableReassessment = true;
};
