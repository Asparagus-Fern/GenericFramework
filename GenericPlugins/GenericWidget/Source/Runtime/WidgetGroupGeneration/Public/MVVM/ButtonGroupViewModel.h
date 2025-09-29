// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "ButtonGroupViewModel.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class WIDGETGROUPGENERATION_API UButtonGroupViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/* Hidden Parent Container Widget When The Button Is Selected, Visible When The Button Is Deselected */
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bShouldHiddenParentContainer = false;
};
