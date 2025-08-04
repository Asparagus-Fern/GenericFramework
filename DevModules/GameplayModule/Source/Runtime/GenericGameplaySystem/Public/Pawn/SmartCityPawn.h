// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonPawn.h"
#include "SmartCityPawn.generated.h"

class UPlayerInputIdleActionComponent;

UCLASS(MinimalAPI)
class ASmartCityPawn : public AThirdPersonPawn
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API ASmartCityPawn(const FObjectInitializer& ObjectInitializer);

	/* IPawnInputMovementInterface */
public:
	GENERICGAMEPLAYSYSTEM_API virtual bool ReassessmentFocus_Implementation() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPlayerInputIdleActionComponent* PlayerInputIdleActionComponent = nullptr;
};
