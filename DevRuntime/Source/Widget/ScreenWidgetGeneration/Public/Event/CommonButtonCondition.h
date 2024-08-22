// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/CommonObject.h"
#include "CommonButtonCondition.generated.h"

class UCommonButton;

/**
 * 按钮执行当前事件的条件
 */
UCLASS(Abstract, EditInlineNew)
class SCREENWIDGETGENERATION_API UCommonButtonCondition : public UCommonObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsConditionPass();
};
