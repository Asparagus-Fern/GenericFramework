// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSettings.h"
#include "SaveGameSettings.generated.h"

class UGenericSaveGameManager;

/**
 * 
 */
UCLASS()
class USaveGameSettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	USaveGameSettings(const FObjectInitializer& ObjectInitializer);
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
	UPROPERTY(Config, EditDefaultsOnly)
	TSoftClassPtr<UGenericSaveGameManager> SaveGameManagerClass;
};
