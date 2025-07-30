// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/ThirdPersonCharacter.h"
#include "TeamCharacter.generated.h"

class UTeamAssignComponent;

UCLASS()
class TEAMASSIGNSYSTEM_API ATeamCharacter : public AThirdPersonCharacter
{
	GENERATED_BODY()

public:
	ATeamCharacter();
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTeamAssignComponent> TeamAssignComponent = nullptr;
};
