// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "Components/CanvasPanelSlot.h"
#include "DynamicPositionWidget.generated.h"

class UCanvasPanelSlot;
class UCanvasPanel;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCanvasPanelWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnchorData LayoutData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoSize = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ZOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Position = FVector2D::Zero();

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// FWidgetContainer WidgetContainer;
};

/**
 * CanvasPanel的包装，用于在屏幕任意处创建指定Widget
 */
UCLASS(Abstract, MinimalAPI)
class UDynamicPositionWidget : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget = "CanvasPanel"))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCanvasPanelWidget> CanvasPanelWidgets;
};
