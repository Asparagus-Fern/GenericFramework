// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Generic/GenericSetting.h"
#include "GenericEdSetting.generated.h"

/**
 * 
 */
UCLASS(Abstract, config=ManagerEdSettings, DefaultConfig)
class DEVEDCORE_API UGenericEdSetting : public UGenericSetting
{
	GENERATED_BODY()

public:
	virtual FName GetCategoryName() const override;
};
