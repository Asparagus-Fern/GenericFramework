// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GameSettings.generated.h"

/**
 * 
 */
UCLASS()
class GAMESETTINGSYSTEM_API UGameSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UGameSettings* GetGameSettings();
};
