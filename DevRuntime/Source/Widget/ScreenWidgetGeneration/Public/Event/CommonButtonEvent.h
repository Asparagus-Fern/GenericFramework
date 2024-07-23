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
class SCREENWIDGETGENERATION_API UCommonButtonEvent : public UCommonObject, public IProcedureInterface
{
	GENERATED_UCLASS_BODY()

public:
	/* 如果为真，则该事件不跟随激活状态而改变，而是会持续激活至按钮被销毁 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPersistent = false;

	/* true则为激活，表示在该条件下激活按钮 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECommonButtonResponseEvent, bool> Response;

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
