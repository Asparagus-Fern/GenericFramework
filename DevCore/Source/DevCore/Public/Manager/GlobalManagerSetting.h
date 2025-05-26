// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSetting.h"
#include "GlobalManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGlobalManagerSetting : public UGenericSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FName GetContainerName() const override { return "Manager"; }
	virtual FName GetCategoryName() const override { return "Global"; }
	virtual FName GetSectionName() const override { return "Global"; }

#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Manager")); }
#endif

public:
	UPROPERTY(Config, EditAnywhere, Category="Global Manager Setting")
	bool bEnableAllManager = true;
};
