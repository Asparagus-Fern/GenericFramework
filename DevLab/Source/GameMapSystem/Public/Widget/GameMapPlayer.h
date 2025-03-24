// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Base/UserWidgetBase.h"
#include "GameMapPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapPlayer : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FImageBrush PlayerImageBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FImageBrush PlayerForwardImageBrush;
};
