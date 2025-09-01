// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "WidgetDescriptionViewModel.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UWidgetDescriptionViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText PrimaryName = FText::FromString("PrimaryName");

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText SecondaryName = FText::FromString("SecondaryName");

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FText TooltipText;
};
