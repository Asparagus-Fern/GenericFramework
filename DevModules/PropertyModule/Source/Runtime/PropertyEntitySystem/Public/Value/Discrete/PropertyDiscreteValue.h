// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/PropertyValueEntity.h"
#include "PropertyDiscreteValue.generated.h"

class UPropertyDiscreteOption;
class FPropertyDataSource;

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue : public UPropertyValueEntity
{
	GENERATED_BODY()

	/* UPropertyEntity */
protected:
	virtual void Startup() override;
	virtual void OnInitialized() override;

	/* UPropertyValueEntity */
public:
	virtual void ResetToDefault() override;
	virtual void StoreToInitial() override;
	virtual void ResetToInitial() override;

	/* UPropertyDiscreteValue */
protected:
	virtual void OnDataSourcesReady();

	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	FString GetDefaultValue() const;
	void SetDefaultValue(FString InValue);

	FString GetValue() const;
	void SetValue(FString InValue);

	void SetDiscreteValue(FString InValue, EPropertyChangeReason Reason);

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	FString DefaultValue;
	FString InitialValue;
};
