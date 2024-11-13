// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValueDynamic.generated.h"

class FPropertyDataSource;

/**
 * 离散类型的属性
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic : public UPropertyDiscreteValue
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
	/* 设置属性的Get函数 */
	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);

	/* 设置属性的Set函数 */
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	/* 获取属性值 */
	FString GetValueAsString() const;

	/* 设置属性值 */
	void SetValueFromString(FString InStringValue);

	/* 获取属性默认值 */
	FString GetDefaultValueAsString() const;

	/* 设置属性默认值 */
	void SetDefaultValueFromString(FString InOptionValue);

	/* 添加属性的一个选项 */
	void AddOption(FString InOptionValue, FText InOptionText);

	/* 移除属性的一个选项 */
	void RemoveOption(FString InOptionValue);

	/* 获取所有的属性选项 */
	const TArray<FString>& GetOptionValues();

	/* 当前属性是否存在指定选项 */
	bool HasOption(const FString& InOptionValue);

protected:
	void SetValueFromString(FString InStringValue, EPropertyChangeReason Reason);

protected:
	/* 默认值 */
	TOptional<FString> DefaultValue;

	/* 初始值 */
	FString InitialValue;

	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	TArray<FString> OptionValues;
	TArray<FText> OptionDisplayTexts;
};
