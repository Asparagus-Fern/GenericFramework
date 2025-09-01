// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "ButtonSelectionViewModel.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETGROUPGENERATION_API UButtonSelectionViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bSelectable = true;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bSelectable"))
	bool bToggleable = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bSelectable"))
	bool bDefaultSelected = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bSelectable"))
	bool bShouldSelectUponReceivingFocus = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bSelectable"))
	bool bInteractableWhenSelected = false;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bSelectable"))
	bool bTriggerClickedAfterSelection = false;
};
