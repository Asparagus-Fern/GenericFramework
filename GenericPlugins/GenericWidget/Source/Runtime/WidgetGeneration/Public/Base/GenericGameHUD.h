// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/GenericWidget.h"
#include "GenericGameHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericGameHUD : public UGenericWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag HUDTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ViewportZOrder = 0;
};
