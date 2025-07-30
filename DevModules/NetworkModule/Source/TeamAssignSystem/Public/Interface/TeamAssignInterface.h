// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.h"
#include "UObject/Interface.h"
#include "TeamAssignInterface.generated.h"

class UTeamAssignPanel;

// This class does not need to be modified.
UINTERFACE()
class UTeamAssignInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAMASSIGNSYSTEM_API ITeamAssignInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void CreatePlayerAssignPanel(TSubclassOf<UTeamAssignPanel> InClass);

	UFUNCTION(BlueprintNativeEvent)
	void UpdatePlayerAssignState(APlayerController* InPlayer, ETeamAssignState InState);

	UFUNCTION(BlueprintNativeEvent)
	void DestroyPlayerAssignPanel();
};
