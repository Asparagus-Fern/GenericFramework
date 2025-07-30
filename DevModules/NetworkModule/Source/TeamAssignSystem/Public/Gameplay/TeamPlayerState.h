// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/GenericPlayerState.h"
#include "TeamPlayerState.generated.h"

class UTeamAssignComponent;

/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamPlayerState : public AGenericPlayerState
{
	GENERATED_BODY()

public:
	ATeamPlayerState();
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTeamAssignComponent> TeamAssignComponent = nullptr;
};
