// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "UniformWidgetWidget.generated.h"

class UCommonButtonGroup;
class UUniformGridPanel;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FUniformGridPanelWidget
{
	GENERATED_BODY()

public:
	/* 行 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Row = 0;

	/* 列 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Colum = 0;

	/* 水平对齐 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Center;

	/* 垂直对齐 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Center;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// FWidgetContainer WidgetContainer;
};

/**
 * UniformGridPanel的包装，用于生成规则大小的Widget块
 */
UCLASS(Abstract, MinimalAPI)
class UUniformWidgetWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget = "UniformGridPanel"), Category="UniformWidgetGroup")
	UUniformGridPanel* UniformGridPanel;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UniformWidgetGroup")
	FMargin SlotPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UniformWidgetGroup")
	float MinDesiredSlotWidth = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UniformWidgetGroup")
	float MinDesiredSlotHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UniformWidgetGroup")
	TArray<FUniformGridPanelWidget> UniformGridPanelWidgets;
};
