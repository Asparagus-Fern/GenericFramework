// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamState.generated.h"

class UTeamAssignComponent;

UCLASS()
class TEAMASSIGNSYSTEM_API ATeamState : public AActor
{
	GENERATED_BODY()

public:
	ATeamState();
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTeamAssignComponent> TeamAssignComponent = nullptr;
};
