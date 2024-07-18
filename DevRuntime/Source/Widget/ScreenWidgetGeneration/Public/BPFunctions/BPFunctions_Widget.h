// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserWidget/Base/UserWidgetType.h"
#include "BPFunctions_Widget.generated.h"

class UMenuStyle;
class UUserWidgetBase;
class UGameHUD;
class UGameMenuSetting;
class UBorder;
class UImage;

DECLARE_DYNAMIC_DELEGATE(FUserWidgetBaseDelegate);

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

	/* HUD */
public:
	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|HUD")
	static TArray<UGameHUD*> GetGameHUD();

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|HUD")
	static TArray<UGameHUD*> GetGameHUDByTag(FGameplayTag InTag);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|HUD")
	static void SetGameHUDVisibility(bool IsVisisble);

	/* User Widget Base */
public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InWidgetClass"), Category="BPFunctions_Widget|UserWidgetBase")
	static UUserWidgetBase* CreateUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InWidgetClass"), Category="BPFunctions_Widget|UserWidgetBase")
	static UUserWidgetBase* OpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass, FUserWidgetBaseDelegate OnFinish);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UserWidgetBase")
	static void OpenUserWidgets(TArray<UUserWidgetBase*> InWidgets);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UserWidgetBase")
	static void OpenUserWidget(UUserWidgetBase* InWidget, FUserWidgetBaseDelegate OnFinish);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UserWidgetBase")
	static void CloseUserWidget(const UUserWidgetBase* InWidget, const FUserWidgetBaseDelegate& OnFinish);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UserWidgetBase")
	static void CloseUserWidgetByTag(FGameplayTag InSlotTag, FUserWidgetBaseDelegate OnFinish);

	/* Menu */
public:
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void SelectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void DeselectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static bool GetMenuContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static bool GetMenuParentContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static bool GetMenuGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static bool GetMenuParentGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static UMenuStyle* GetMenuStyle(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static UMenuStyle* GetParentMenuStyle(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static TArray<UMenuStyle*> GetAllMenuStyle();

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static FGameplayTag GetLastActiveMenuTag();

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static FGameplayTag GetCurrentActiveMenuTag();
};
