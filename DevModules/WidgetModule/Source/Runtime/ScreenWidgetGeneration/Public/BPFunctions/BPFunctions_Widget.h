// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetManager.h"
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

	/* Interactable Widget Group */
public:
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Interactable")
	static void AddInteractableWidget(UInteractableWidgetBase* InteractableWidget, FString GroupName);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Interactable")
	static void RemoveInteractableWidget(UInteractableWidgetBase* InteractableWidget, FString GroupName);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Interactable")
	static void ClearupInteractableWidgetGroup(const FString& GroupName, bool DeselectAll);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Interactable")
	static bool GetInteractableWidgetGroups(TMap<FString, UCommonButtonGroup*>& Groups);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Interactable")
	static bool FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group);

	/* HUD */
public:
	/* 获取当前所有的HUD */
	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|HUD")
	static bool GetGameHUDs(TArray<UGameHUD*>& GameHUDs);

	/* 通过HUD的SelfTag获取对应的HUD */
	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|HUD")
	static bool GetGameHUDByTag(FGameplayTag InTag, TArray<UGameHUD*>& GameHUDs);

	/* 设置所有HUD的激活状态 */
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|HUD")
	static void SetAllGameHUDActiveState(bool IsVisisble);

	/* 设置HUD的激活状态 */
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|HUD")
	static void SetGameHUDActiveState(UGameHUD* GameHUD, bool IsVisisble);

	/* 通过Tag查找对应的HUD并设置激活状态*/
	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="UI.HUD"), Category="BPFunctions_Widget|HUD")
	static void SetGameHUDActiveStateByTag(FGameplayTag InTag, bool IsVisisble);





	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.HUD", DeterminesOutputType = "InClass"), Category="BPFunctions_Widget|Slot")
	static UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag);

	/* UserWidgetBase */
public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InWidgetClass"), Category="BPFunctions_Widget|UserWidgetBase")
	static UUserWidgetBase* OpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass);

	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|UserWidgetBase")
	static void OpenUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = 1), Category="BPFunctions_Widget|UserWidgetBase")
	static void CloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="UI.HUD", AdvancedDisplay = 1), Category="BPFunctions_Widget|UserWidgetBase")
	static void CloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="UI.HUD"), Category="BPFunctions_Widget|UserWidgetBase")
	static void MoveUserWidget(FGameplayTag OriginSlotTag, FGameplayTag TargetSlotTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|UserWidgetBase")
	static bool GetActivedWidgets(TArray<UUserWidgetBase*>& ActivedWidgets);

	/* Game Menu */
public:
	UFUNCTION(BlueprintCallable, Category="BPFunctions_Widget|Menu")
	static void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);

	UFUNCTION(BlueprintCallable, meta=( GameplayTagFilter="UI.Menu"), Category="BPFunctions_Widget|Menu")
	static void SelectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintCallable, meta=( GameplayTagFilter="UI.Menu"), Category="BPFunctions_Widget|Menu")
	static void DeselectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static UGameMenuSetting* GetGameMenu(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="BPFunctions_Widget|Menu")
	static bool GetMenuGenerateInfos(TArray<FMenuGenerateInfo>& MenuGenerateInfos);
};
