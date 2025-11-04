// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Settings/GenericSettings.h"
#include "GenericEdSettings.generated.h"

/**
 * 
 */
UCLASS(Abstract, config=GenericEdSettings, DefaultConfig)
class DEVEDCORE_API UGenericEdSettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override { return TEXT("Editor"); }
};
