// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
// #include "PropertyDiscreteValueInterface.generated.h"

class FPropertyDataSource;

/**
 * 
 */
class PROPERTYPATHSYSTEM_API FPropertyDiscreteValueInterface
{
public:
	virtual ~FPropertyDiscreteValueInterface() = default;

	/* 设置属性的Get函数 */
	virtual void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);

	/* 设置属性的Set函数 */
	virtual void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	/* 获取属性值 */
	virtual FString GetValueAsString() const PURE_VIRTUAL(, return TEXT(""););

	/* 设置属性值 */
	virtual void SetValueFromString(FString InStringValue) PURE_VIRTUAL(,);

	/* 设置属性值 */
	virtual void SetValueFromString(FString InStringValue, EPropertyChangeReason Reason) PURE_VIRTUAL(,);

	/* 获取属性默认值 */
	FString GetDefaultValueAsString() const;

	/* 设置属性默认值 */
	void SetDefaultValueFromString(const FString& InOptionValue);

public:
	/* 当前属性是否存在指定选项 */
	virtual bool HasOption(const FString& InOptionValue);

	/* 获取所有的属性值 */
	virtual const TArray<FString>& GetAllOptionValue();

	/* 获取所有的属性显示名 */
	virtual TArray<FText> GetAllOptionText() const;

	/* 添加属性的一个选项 */
	void AddOption(const FString& InOptionValue, const FText& InOptionText);

	/* 移除属性的一个选项 */
	void RemoveOption(const FString& InOptionValue);

	/* 获取当前选中选项的Index */
	virtual int32 GetDiscreteOptionIndex() const;

	/* 通过Index设置选项 */
	virtual void SetDiscreteOptionByIndex(int32 Index);

	/* 获取默认选项的Index */
	virtual int32 GetDiscreteOptionDefaultIndex() const;

	/* 通过Index设置选项 */
	virtual void SetDiscreteDefaultOptionByIndex(int32 Index);

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	/* 默认值 */
	TOptional<FString> DefaultValue;

	/* 初始值 */
	FString InitialValue;

	TArray<FString> OptionValues;
	TArray<FText> OptionDisplayTexts;
};
