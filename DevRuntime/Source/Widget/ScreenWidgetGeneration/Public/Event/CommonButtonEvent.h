// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Object/CommonObject.h"
#include "UObject/ObjectMacros.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "CommonButtonEvent.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class SCREENWIDGETGENERATION_API UCommonButtonEvent : public UCommonObject, public IProcedureInterface, public IProcedureBaseInterface
{
	GENERATED_UCLASS_BODY()

public:
	/* true则为激活，表示在该条件下激活按钮 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECommonButtonResponseEvent, bool> ResponseEvent;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
};
