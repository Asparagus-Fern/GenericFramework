// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVM/PropertyViewModel.h"
#include "DataPropertyViewModel.generated.h"

/**
 * Data Type Property
 */
UCLASS(Abstract, MinimalAPI)
class UDataPropertyViewModel : public UPropertyViewModel
{
	GENERATED_BODY()

protected:
	PROPERTYSYSTEM_API virtual bool OnPropertyInitialized() override;
	PROPERTYSYSTEM_API virtual void OnPropertyDeinitialized() override;
	PROPERTYSYSTEM_API virtual void OnPropertyApply() override;
	PROPERTYSYSTEM_API virtual void OnPropertyReverse() override;
	PROPERTYSYSTEM_API virtual void OnPropertyReset() override;
	PROPERTYSYSTEM_API virtual void OnPropertyDependencyValueChanged(UPropertyViewModel* InDependencyProperty, EPropertyChangedReason ChangedReason) override;

public:
	PROPERTYSYSTEM_API UPropertyDataSource* GetPropertyDataSource();
	PROPERTYSYSTEM_API void SetPropertyDataSource(UPropertyDataSource* InPropertyDataSource);

	PROPERTYSYSTEM_API virtual FString GetInitialValueAsString() PURE_VIRTUAL(, return TEXT("");)
	PROPERTYSYSTEM_API virtual void SetInitialValueFromString(const FString& InValue) PURE_VIRTUAL(,)
	PROPERTYSYSTEM_API virtual FString GetCurrentValueAsString() PURE_VIRTUAL(, return TEXT("");)
	PROPERTYSYSTEM_API virtual void SetCurrentValueFromString(const FString& InValue) PURE_VIRTUAL(,)

private:
	UPROPERTY()
	TObjectPtr<UPropertyDataSource> PropertyDataSource = nullptr;
};
