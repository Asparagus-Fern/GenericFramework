// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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

	/* HUD */
public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"), Category="BPFunctions_Widget|HUD")
	static bool GetGameHUDs(const UObject* WorldContextObject, TArray<UGameHUD*>& GameHUDs);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"), Category="BPFunctions_Widget|HUD")
	static bool GetGameHUDByTag(const UObject* WorldContextObject, FGameplayTag InTag, TArray<UGameHUD*>& GameHUDs);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="BPFunctions_Widget|HUD")
	static void SetAllGameHUDVisibility(const UObject* WorldContextObject, bool IsVisisble);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="BPFunctions_Widget|HUD")
	static void SetGameHUDVisibility(const UObject* WorldContextObject, UGameHUD* GameHUD, bool IsVisisble);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="BPFunctions_Widget|HUD")
	static void SetGameHUDVisibilityByTag(const UObject* WorldContextObject, FGameplayTag InTag, bool IsVisisble);

	/*
	/* Slot #1#
public:
	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Slot", meta=(GameplayTagFilter="HUD"))
	static UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Slot", meta=(GameplayTagFilter="HUD", DeterminesOutputType = "InClass"))
	static UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag, TSubclassOf<UUserWidgetBase> InClass);

	/* User Widget Base #1#
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

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UserWidgetBase", meta=(GameplayTagFilter="HUD"))
	static void CloseUserWidgetByTag(FGameplayTag InSlotTag, FUserWidgetBaseDelegate OnFinish);

	/* Menu #1#
public:
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static void SelectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static void DeselectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static bool GetMenuContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static bool GetMenuParentContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static bool GetMenuGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static bool GetMenuParentGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static UMenuStyle* GetMenuStyle(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu", meta=(GameplayTagFilter="Menu"))
	static UMenuStyle* GetParentMenuStyle(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static TArray<UMenuStyle*> GetAllMenuStyle();

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static FGameplayTag GetLastActiveMenuTag();

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static FGameplayTag GetCurrentActiveMenuTag();*/
};
