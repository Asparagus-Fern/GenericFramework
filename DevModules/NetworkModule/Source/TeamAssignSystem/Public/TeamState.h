// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.h"
#include "GameFramework/Actor.h"
#include "TeamState.generated.h"

UCLASS()
class TEAMASSIGNSYSTEM_API ATeamState : public AActor
{
	GENERATED_BODY()

public:
	ATeamState();
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

public:
	/* Init Only In Server */
	UFUNCTION(BlueprintImplementableEvent)
	void InitTeamState(int32 InTeamID);
};
