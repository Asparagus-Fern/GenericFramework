// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Procedure/ProcedureInterface.h"
#include "UObject/Object.h"
#include "CommonButtonEvent.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class SCREENWIDGETGENERATION_API UCommonButtonEvent : public UObject, public IProcedureInterface
{
	GENERATED_BODY()

public:
	/* true则为激活，表示在该条件下激活按钮 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECommonButtonResponseEvent, bool> ResponseEvent;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;
};
