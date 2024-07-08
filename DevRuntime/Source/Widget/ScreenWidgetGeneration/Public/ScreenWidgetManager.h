// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetType.h"
#include "Manager/CoreManager.h"
#include "Procedure/ProcedureType.h"
#include "ScreenWidgetManager.generated.h"

class UWidget;
class UTagNameSlot;
class UGameWidgetSetting;
class UGameLoading;
class UGameHUD;
class UGameMenuSetting;
class UUserWidgetBase;

DECLARE_DYNAMIC_DELEGATE(FOnUserWidgetHandleFinish);

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UScreenWidgetManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UScreenWidgetManager();

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IManagerInterface  */
public:
	virtual FText GetManagerDisplayName() override;

	/* UTagNameSlot */
protected:
	UPROPERTY()
	TMap<FGameplayTag, UTagNameSlot*> Slots;

	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<FGameplayTag, UUserWidgetBase*> SlotWidgets;

public:
	void RegisterSlot(UTagNameSlot* InSlot);
	void UnRegisterSlot(const UTagNameSlot* InSlot);

public:
	UFUNCTION(BlueprintPure)
	UTagNameSlot* GetSlot(FGameplayTag InSlotTag) const;

	UFUNCTION(BlueprintPure)
	UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag) const;

	UFUNCTION(BlueprintPure, meta = ( DeterminesOutputType = "InClass"))
	UUserWidgetBase* GetSlotUserWidgetByClass(FGameplayTag InSlotTag, TSubclassOf<UUserWidgetBase> InClass) const;

	/* Game HUD */
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="Game HUD Classes")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;

protected:
	void CreateGameHUD();

	/* User Widget Base */
public:
	virtual UUserWidgetBase* CreateUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass);
	virtual UUserWidgetBase* OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void OpenUserWidget(TArray<UUserWidgetBase*> InWidgets);
	virtual void OpenUserWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void CloseUserWidget(const UUserWidgetBase* InWidget, const FSimpleMulticastDelegate& OnFinish = FSimpleMulticastDelegate());
	virtual void CloseUserWidget(FGameplayTag InSlotTag, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());

	TArray<FProcedureInterfaceHandle> GetProcedureInterfaceHandles(UUserWidget* InWidget, bool TargetActiveState);
	virtual TArray<IProcedureInterface*> GetProcedureInterfaceWidgets(UUserWidget* InWidget);

protected:
	virtual void ActiveWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void InactiveWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());

	/* Game Menu */
public:
	UPROPERTY(BlueprintReadOnly, Transient)
	UGameMenuSetting* GameMenu = nullptr;

	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FMenuGenerateInfo> MenuGenerateInfos;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);

	UFUNCTION(BlueprintCallable)
	void SelectMenu(FGameplayTag InMenuTag);

	UFUNCTION(BlueprintCallable)
	void DeselectMenu(FGameplayTag InMenuTag);
	
	UFUNCTION(BlueprintPure)
	virtual bool GetMenuContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure)
	virtual bool GetMenuParentContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);

	UFUNCTION(BlueprintPure)
	virtual bool GetMenuGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);

	UFUNCTION(BlueprintPure)
	virtual bool GetMenuParentGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);

	UFUNCTION(BlueprintPure)
	virtual UMenuStyle* GetMenuStyle(FGameplayTag InMenuTag);

protected:
	FDelegateHandle MenuSelectionChangedHandle;
	virtual void GenerateMenu(FMenuContainerInfo InMenuContainerInfo);
	virtual void OnMenuSelectionChanged(FMenuInfo InMenuInfo, bool bSelection);

private:
	TMap<FGameplayTag, bool> TargetMenuSelection;
	int32 TargetMenuSelectionIndex = 0;
	virtual void HandleMenuSelectionChanged();
	virtual void HandleMenuSelectionChangedOnceFinish();
};
