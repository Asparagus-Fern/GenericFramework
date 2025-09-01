// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GenericWidgetViewModel.generated.h"

class UWidgetRenderViewModel;
class UWidgetDescriptionViewModel;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UGenericWidgetViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UWidgetDescriptionViewModel> WidgetDescriptionViewModel = nullptr;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite, Instanced)
	TObjectPtr<UWidgetRenderViewModel> WidgetRenderViewModel = nullptr;
};
