// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValueInterface.h"
#include "Value/PropertyValueBase.h"
#include "PropertyDiscreteValue.generated.h"

class FPropertyDataSource;

/**
 * 离散类型的属性
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue : public UPropertyValueBase, public FPropertyDiscreteValueInterface
{
	GENERATED_BODY()

	/* UPropertyEntity */
public:
	virtual void OnInitialized() override;
	virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	virtual void StoreInitial() override;
	virtual void ResetToInitial() override;
	virtual void ResetToDefault() override;

	/* FPropertyDiscreteValueInterface */
public:
	/* 获取属性值 */
	virtual FString GetValueAsString() const override;

	/* 设置属性值 */
	virtual void SetValueFromString(FString InStringValue) override;

	/* 设置属性值 */
	virtual void SetValueFromString(FString InStringValue, EPropertyChangeReason Reason) override;

	virtual const TArray<FString>& GetAllOptionValue() override;
	virtual TArray<FText> GetAllOptionText() const override;
};
