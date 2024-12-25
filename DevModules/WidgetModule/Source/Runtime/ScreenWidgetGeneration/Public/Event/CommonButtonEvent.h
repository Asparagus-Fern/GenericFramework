// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "UObject/ObjectMacros.h"
#include "Procedure/ProcedureObject.h"
#include "CommonButtonEvent.generated.h"

class UCommonButtonCondition;

/**
 *	todo:流程类将重写
 * 按钮事件
 */
UCLASS(Abstract, EditInlineNew)
class SCREENWIDGETGENERATION_API UCommonButtonEvent : public UProcedureObject
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UCommonButtonEvent */
public:
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	// TArray<UCommonButtonCondition*> CommonButtonConditions;

public:
	UFUNCTION(BlueprintNativeEvent)
	bool CanExecuteButtonEvent();

	UFUNCTION(BlueprintNativeEvent)
	void ExecuteButtonEvent();
};
