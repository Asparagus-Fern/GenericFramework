// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserWidget/Base/UserWidgetType.h"
#include "BPFunctions_Widget.generated.h"

class UGameMenuSetting;
class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UBPFunctions_Widget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* UWidget */
public:
	UFUNCTION(BlueprintPure, DisplayName="IsValid(ImageBrush)", meta=(CompactNodeTitle = "IsValid"), Category="BPFunctions_Widget|UWidget")
	static bool IsValid_ImageBrush(const FImageBrush& InImageBrush);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UWidget")
	static void SetImageBrush(UImage* InImage, FImageBrush InImageBrush);

	UFUNCTION(BlueprintPure, DisplayName="IsValid(BorderBrush)", meta=(CompactNodeTitle = "IsValid"), Category="BPFunctions_Widget|UWidget")
	static bool IsValid_BorderBrush(const FBorderBrush& InBorderBrush);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UWidget")
	static void SetBorderBrush(UBorder* InBorder, FBorderBrush InBorderBrush);

	/* Menu */
public:
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void SelectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void DeselectMenu(FGameplayTag InMenuTag);
};
