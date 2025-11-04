// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericSettings.h"
#include "GenericGlobalSettings.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGenericGlobalSettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FName GetContainerName() const override { return "GenericFramework"; }
	virtual FName GetCategoryName() const override { return "Global"; }
	virtual FName GetSectionName() const override { return "Global"; }

public:
	UPROPERTY(Config, EditAnywhere)
	bool bTest = false;
};
