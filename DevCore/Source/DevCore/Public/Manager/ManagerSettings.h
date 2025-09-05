// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSettings.h"
#include "ManagerSettings.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UManagerSettings : public UGenericSettings
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }
	virtual FName GetContainerName() const override { return "Manager"; }
	virtual FName GetCategoryName() const override { return "Global"; }
	virtual FName GetSectionName() const override { return "Global"; }

public:
	UPROPERTY(Config, EditAnywhere)
	bool bEnableAllManager = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UDataTable>> GameplayTagTables;
};
