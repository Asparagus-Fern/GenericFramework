// Copyright ChenTaiye 2025. All Rights Reserved.

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
