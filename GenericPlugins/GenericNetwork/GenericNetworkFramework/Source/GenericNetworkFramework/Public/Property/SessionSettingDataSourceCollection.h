// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "DataSource/PropertyDataSourceCollection.h"
#include "SessionSettingDataSourceCollection.generated.h"

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSettingDataSourceCollection : public UPropertyDataSourceCollection
{
	GENERATED_BODY()

public:
	virtual void GeneratePropertyViewModels_Implementation(TArray<UPropertyViewModel*>& Result) override;
	virtual void OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel) override;
	virtual void OnPropertyReset_Implementation(UPropertyViewModel* InPropertyViewModel) override;

public:
	UFUNCTION()
	void SetSessionSettings(const FGenericSessionSettings& InSettings);

protected:
	UPROPERTY()
	FGenericSessionSettings SessionSettings;
};
