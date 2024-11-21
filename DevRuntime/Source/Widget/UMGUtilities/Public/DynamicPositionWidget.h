// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Components/CanvasPanelSlot.h"
#include "UserWidget/Base/UserWidgetBase.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWidgetContainer WidgetContainer;
};

/**
 * CanvasPanel的包装，用于在屏幕任意处创建指定Widget
 */
UCLASS(Abstract)
class UMGUTILITIES_API UDynamicPositionWidget : public UUserWidgetBase
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
