// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Components/SlateWrapperTypes.h"
#include "Slate/WidgetTransform.h"
#include "WidgetRenderViewModel.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class WIDGETGENERATION_API UWidgetRenderViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	ESlateVisibility Visibility = ESlateVisibility::SelfHitTestInvisible;

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FVector2D RenderTransformPivot = FVector2D(0.5f, 0.5f);

	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	FWidgetTransform RenderTransform;
};
