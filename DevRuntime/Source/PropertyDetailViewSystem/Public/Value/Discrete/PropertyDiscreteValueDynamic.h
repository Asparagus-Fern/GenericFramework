// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValueDynamic.generated.h"

class FPropertyDataSource;

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic : public UPropertyDiscreteValue
{
	GENERATED_BODY()

	/* UPropertyEntity */
public:
	virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;

	/* UPropertyDiscreteValue */
public:
	virtual void SetDiscreteOptionByIndex(int32 Index) override;
	virtual int32 GetDiscreteOptionIndex() const override;
	virtual int32 GetDiscreteOptionDefaultIndex() const override;
	virtual TArray<FText> GetDiscreteOptions() const override;

	/* UPropertyDiscreteValueDynamic */
public:
	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	FString GetValueAsString() const;
	void SetValueFromString(FString InStringValue);
	void SetDefaultValueFromString(FString InOptionValue);

	void AddOption(FString InOptionValue, FText InOptionText);
	void RemoveOption(FString InOptionValue);

	const TArray<FString>& GetOptionValues();
	bool HasOption(const FString& InOptionValue);

protected:
	void SetValueFromString(FString InStringValue, EPropertyChangeReason Reason);

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	TOptional<FString> DefaultValue;
	FString InitialValue;

	TArray<FString> OptionValues;
	TArray<FText> OptionDisplayTexts;
};
