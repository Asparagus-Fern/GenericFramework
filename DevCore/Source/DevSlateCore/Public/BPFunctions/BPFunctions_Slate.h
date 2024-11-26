// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Slate.generated.h"

class USpline2DSlot;
class UBackgroundBlurSlot;
class UWidget;
class UButtonSlot;
class UStackBoxSlot;
class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UBPFunctions_Slate : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Layout */
public:
	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static UStackBoxSlot* SlotAsStackBoxSlot(const UWidget* Widget);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static UButtonSlot* SlotAsButtonSlot(const UWidget* Widget);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static UBackgroundBlurSlot* SlotAsBackgroundBlurSlot(const UWidget* Widget);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Slate|Slot")
	static USpline2DSlot* SlotAsSpline2DSlot(const UWidget* Widget);

	/* Image */
public:
	UFUNCTION(BlueprintPure, DisplayName="IsValid(ImageBrush)", meta=(CompactNodeTitle = "IsValid"), Category="BPFunctions_Slate|Image")
	static bool IsValid_ImageBrush(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Slate|Image")
	static void SetImageBrush(UImage* InImage, FImageBrush InImageBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Image Brush", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FImageBrush ConvToImageBrush(const FSlateBrush& InSlateBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Brush(Image)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Image")
	static FSlateBrush Image_ConvToSlateBrush(const FImageBrush& InImageBrush);

	/* Border */
public:
	UFUNCTION(BlueprintPure, DisplayName="IsValid(BorderBrush)", meta=(CompactNodeTitle = "IsValid"), Category="BPFunctions_Slate|Border")
	static bool IsValid_BorderBrush(const FBorderBrush& InBorderBrush);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Slate|Border")
	static void SetBorderBrush(UBorder* InBorder, FBorderBrush InBorderBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Border Brush", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FBorderBrush ConvToBorderBrush(const FSlateBrush& InSlateBrush);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Slate Brush(Border)", CompactNodeTitle = "->", BlueprintAutocast), Category="BPFunctions_Slate|Border")
	static FSlateBrush Border_ConvToSlateBrush(const FBorderBrush& InBorderBrush);
};
