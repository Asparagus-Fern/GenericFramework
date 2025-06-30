// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/ThirdPersonCharacter.h"
#include "TeamCharacter.generated.h"

UCLASS()
class TEAMASSIGNSYSTEM_API ATeamCharacter : public AThirdPersonCharacter
{
	GENERATED_BODY()

public:
	ATeamCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
};
