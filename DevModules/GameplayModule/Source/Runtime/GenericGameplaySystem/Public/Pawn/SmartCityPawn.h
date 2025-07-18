// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonPawn.h"
#include "SmartCityPawn.generated.h"

class UPlayerInputIdleActionComponent;

UCLASS()
class GENERICGAMEPLAYSYSTEM_API ASmartCityPawn : public AThirdPersonPawn
{
	GENERATED_BODY()

public:
	ASmartCityPawn(const FObjectInitializer& ObjectInitializer);

	/* IPawnInputMovementInterface */
public:
	virtual bool ReassessmentFocus_Implementation() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPlayerInputIdleActionComponent* PlayerInputIdleActionComponent = nullptr;
};
