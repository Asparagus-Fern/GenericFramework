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
UCLASS(MinimalAPI)
class UPropertyDiscreteValue : public UPropertyValueBase, public FPropertyDiscreteValueInterface
{
	GENERATED_BODY()

	/* UPropertyEntity */
public:
	PROPERTYPATHSYSTEM_API virtual void OnInitialized() override;
	PROPERTYPATHSYSTEM_API virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	PROPERTYPATHSYSTEM_API virtual void StoreInitial() override;
	PROPERTYPATHSYSTEM_API virtual void ResetToInitial() override;
	PROPERTYPATHSYSTEM_API virtual void ResetToDefault() override;

	/* FPropertyDiscreteValueInterface */
public:
	/* 获取属性值 */
	PROPERTYPATHSYSTEM_API virtual FString GetValueAsString() const override;

	/* 设置属性值 */
	PROPERTYPATHSYSTEM_API virtual void SetValueFromString(FString InStringValue) override;

	/* 设置属性值 */
	PROPERTYPATHSYSTEM_API virtual void SetValueFromString(FString InStringValue, EPropertyChangeReason Reason) override;

	PROPERTYPATHSYSTEM_API virtual const TArray<FString>& GetAllOptionValue() override;
	PROPERTYPATHSYSTEM_API virtual TArray<FText> GetAllOptionText() const override;
};
