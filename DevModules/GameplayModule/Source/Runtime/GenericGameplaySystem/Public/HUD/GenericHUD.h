// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GenericHUD.generated.h"

/**
 * 
 */
UCLASS()
class GENERICGAMEPLAYSYSTEM_API AGenericHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	virtual void DrawHUD() override;
};
