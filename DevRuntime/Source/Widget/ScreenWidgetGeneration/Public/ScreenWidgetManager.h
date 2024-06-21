// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetType.h"
#include "Manager/CoreManager.h"
#include "ScreenWidgetManager.generated.h"

class UWidget;
class UTagNameSlot;
class UGameWidgetSetting;
class UGameLoading;
class UGameHUD;
class UGameMenuSetting;
class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UScreenWidgetManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UScreenWidgetManager();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	static UScreenWidgetManager* Get();

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativePostProcedureSwitch(EGameplayProcedure InProcedure) override;
	virtual void NativeOnInactived() override;

	/* UTagNameSlot */
public:
	void RegisterSlot(UTagNameSlot* InSlot);

protected:
	UPROPERTY()
	TMap<FGameplayTag, UTagNameSlot*> Slots;

	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<FGameplayTag, UUserWidgetBase*> SlotWidgets;

public:
	UFUNCTION(BlueprintPure)
	UTagNameSlot* GetSlot(FGameplayTag InSlotTag) const;

	UFUNCTION(BlueprintPure)
	UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag) const;

	UFUNCTION(BlueprintPure, meta = ( DeterminesOutputType = "InClass"), Category="Slot Manager")
	UUserWidgetBase* GetSlotUserWidgetByClass(FGameplayTag InSlotTag, TSubclassOf<UUserWidgetBase> InClass) const;

	/* Game HUD */
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;

protected:
	void CreateGameHUD();

	/* User Widget Base */
public:
	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType = "InWidgetClass"))
	UUserWidgetBase* OpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass);

	UFUNCTION(BlueprintCallable)
	void OpenUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable)
	void CloseUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable)
	void CloseUserWidgetBySlotTag(FGameplayTag InSlotTag);

	/* Game Menu */
public:
	UPROPERTY(BlueprintReadOnly, Transient)
	UGameMenuSetting* GameMenu = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);

	UFUNCTION(BlueprintCallable)
	void GenerateMenu(FMenuContainerInfo InMenuContainerInfo);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FMenuGenerateInfo> MenuGenerateInfos;

protected:
	FDelegateHandle MenuSelectionChangedHandle;
	void OnMenuSelectionChanged(FMenuInfo InMenuInfo, bool bSelection);
};
