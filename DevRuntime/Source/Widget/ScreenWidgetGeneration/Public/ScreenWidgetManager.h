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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuGenerateInfoDelegate, FMenuGenerateInfo, MenuGenerateInfo);

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UScreenWidgetManager : public UCoreManager
{
	GENERATED_BODY()

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
	UPROPERTY(Config, EditAnywhere, DisplayName="Game HUD Classes")
	TArray<TSoftClassPtr<UGameHUD>> GameHUDClasses;

protected:
	UPROPERTY(Transient)
	TArray<UGameHUD*> GameHUD;

public:
	virtual TArray<UGameHUD*> GetGameHUD();
	virtual TArray<UGameHUD*> GetGameHUDByTag(FGameplayTag InTag);
	virtual void SetGameHUDVisibility(bool IsVisisble);

protected:
	void CreateGameHUD();

	/* User Widget Base */
public:
	virtual UUserWidgetBase* CreateUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass);
	virtual UUserWidgetBase* OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void OpenUserWidget(TArray<UUserWidgetBase*> InWidgets);
	virtual void OpenUserWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void CloseUserWidget(const UUserWidgetBase* InWidget, const FSimpleMulticastDelegate& OnFinish = FSimpleMulticastDelegate());
	virtual void CloseUserWidget(TArray<UUserWidgetBase*> InWidgets);
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
	UPROPERTY(BlueprintAssignable)
	FMenuGenerateInfoDelegate OnMenuGenerate;

public:
	virtual void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);
	virtual void SelectMenu(FGameplayTag InMenuTag);
	virtual void DeselectMenu(FGameplayTag InMenuTag);
	virtual bool GetMenuContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);
	virtual bool GetMenuParentContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo);
	virtual bool GetMenuGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);
	virtual bool GetMenuParentGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo);
	virtual UMenuStyle* GetMenuStyle(FGameplayTag InMenuTag);
	virtual UMenuStyle* GetParentMenuStyle(FGameplayTag InMenuTag);
	virtual TArray<UMenuStyle*> GetAllMenuStyle();
	virtual FGameplayTag GetLastActiveMenuTag() { return LastActiveMenuTag; }
	virtual FGameplayTag GetCurrentActiveMenuTag() { return CurrentActiveMenuTag; }

protected:
	FGameplayTag LastActiveMenuTag;
	FGameplayTag CurrentActiveMenuTag;
	virtual void GenerateMenu(FMenuContainerInfo InMenuContainerInfo);

protected:
	FDelegateHandle MenuSelectionChangedHandle;
	TMap<FGameplayTag, bool> TargetMenuSelection;
	FTimerHandle UpdateMenuSelectionHandle;
	int32 TargetMenuSelectionIndex = 0;

	virtual void OnMenuSelectionChanged(FMenuInfo InMenuInfo, bool bSelection);
	virtual void UpdateActiveMenutag();
	virtual void HandleMenuSelectionChangedNextTick();
	virtual void HandleMenuSelectionChanged();
	virtual void ActiveMenu(FGameplayTag InMenuTag, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void InactiveMenu(FGameplayTag InMenuTag, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void ActiveParentMenu(FGameplayTag InMenuTag, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void InactiveParentMenu(FGameplayTag InMenuTag, FSimpleMulticastDelegate OnFinish = FSimpleMulticastDelegate());
	virtual void HandleMenuSelectionChangedOnceFinish();
	virtual void HandleMenuSelectionChangedFinish();
};
