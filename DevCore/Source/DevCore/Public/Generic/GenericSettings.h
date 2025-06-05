// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GenericSettings.generated.h"

/**
 * 
 */
UCLASS(Abstract, config=GenericSettings, DefaultConfig)
class DEVCORE_API UGenericSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;
};
