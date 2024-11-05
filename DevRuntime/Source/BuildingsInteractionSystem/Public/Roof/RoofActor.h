// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Floor/FloorActor.h"
#include "RoofActor.generated.h"

UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API ARoofActor : public AFloorActor
{
	GENERATED_BODY()

public:
	ARoofActor();
	virtual void BeginPlay() override;
};
