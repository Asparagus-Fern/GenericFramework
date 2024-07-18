// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanelSlot.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "DynamicScreenPositionBox.generated.h"

class UCanvasPanelSlot;
class UCanvasPanel;


USTRUCT(BlueprintType)
struct FDynamicWidget
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UUserWidgetBase* Widget;
};

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UDynamicScreenPositionBox : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget = "CanvasPanel"))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDynamicWidget> DynamicWidgets;
};
