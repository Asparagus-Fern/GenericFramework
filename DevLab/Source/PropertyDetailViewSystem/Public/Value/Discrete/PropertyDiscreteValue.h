// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/PropertyValueBase.h"
#include "PropertyDiscreteValue.generated.h"

/**
 * 离散类型的属性基类
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValue : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	/* 通过Index设置选项 */
	UFUNCTION(BlueprintCallable)
	virtual void SetDiscreteOptionByIndex(int32 Index) PURE_VIRTUAL(,);

	/* 获取当前选中选项的Index */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetDiscreteOptionIndex() const PURE_VIRTUAL(, return INDEX_NONE;);

	/* 获取默认选项的Index */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetDiscreteOptionDefaultIndex() const { return INDEX_NONE; }

	/* 获取所有的选项 */
	UFUNCTION(BlueprintCallable)
	virtual TArray<FText> GetDiscreteOptions() const PURE_VIRTUAL(, return TArray<FText>(););
};
