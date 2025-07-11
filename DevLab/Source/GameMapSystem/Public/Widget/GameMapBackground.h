// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Base/GenericWidget.h"
#include "GameMapBackground.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapBackground : public UGenericWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FImageBrush BackgroundImageBrush;
};
