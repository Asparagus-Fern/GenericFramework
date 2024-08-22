// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Object/CommonObject.h"
#include "UObject/ObjectMacros.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "Procedure/ProcedureObject.h"
#include "CommonButtonEvent.generated.h"

class UCommonButtonCondition;
/**
 * 按钮状态发生更改执行的事件
 */
UCLASS(Abstract, EditInlineNew)
class SCREENWIDGETGENERATION_API UCommonButtonEvent : public UProcedureObject
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonCondition*> CommonButtonConditions;

public:
	UFUNCTION(BlueprintNativeEvent)
	void ExecuteButtonEvent();
};
