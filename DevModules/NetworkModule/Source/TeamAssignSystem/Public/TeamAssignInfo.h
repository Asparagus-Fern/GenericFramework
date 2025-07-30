// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "TeamAssignInfo.generated.h"

class UTeamAssignComponent;
class ATeamPlayerState;
class ATeamState;

/**
 * 
 */
UCLASS(MinimalAPI)
class UTeamAssignInfo : public UGenericObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 TeamID = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<ATeamState> TeamState = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<APlayerController>> PlayerList;

	UPROPERTY()
	TArray<TObjectPtr<UTeamAssignComponent>> TeamComponents;
};
