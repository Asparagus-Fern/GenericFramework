// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GenericWidgetInfo.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UGenericWidgetInfo : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/* 主要名字 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText MainName;

	/* 次要名字 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SubName;

	/* 提示 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ToolTip;

	/* 图标 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;
};
