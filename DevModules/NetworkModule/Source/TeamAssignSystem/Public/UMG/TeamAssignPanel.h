// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamType.h"
#include "Base/GenericWidget.h"
#include "TeamAssignPanel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Abstract)
class UTeamAssignPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayerAssignState(APlayerController* InPlayer, ETeamAssignState InState);
};
