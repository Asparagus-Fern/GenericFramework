// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetType.h"
#include "Manager/CoreManager.h"
#include "Procedure/ProcedureType.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "ScreenWidgetManager.generated.h"

class UCommonButtonBase;
class UInstanceUserWidgetBase;
class UGameplayTagSlot;
class UWidget;
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
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScreenWidgetDelegate);

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* Interactable Widget Group */
public:
	void AddInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);
	void RemoveInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);
	void ClearupInteractableWidgetGroup(const FString& GroupName, bool DeselectAll);
	bool FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const;

protected:
	TMap<FString, UCommonButtonGroup*> InteractableWidgetGroups;

	/* Game HUD */
public:
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<UGameHUD*> GameHUDs;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHUDDelegate, UGameHUD*, HUD);

	UPROPERTY(BlueprintAssignable)
	FScreenWidgetDelegate PreHUDCreated;

	UPROPERTY(BlueprintAssignable)
	FHUDDelegate OnHUDCreated;

	UPROPERTY(BlueprintAssignable)
	FScreenWidgetDelegate PostHUDCreated;

	UPROPERTY(BlueprintAssignable)
	FScreenWidgetDelegate PreHUDDestroyed;

	UPROPERTY(BlueprintAssignable)
	FHUDDelegate OnHUDDestroyed;

	UPROPERTY(BlueprintAssignable)
	FScreenWidgetDelegate PostHUDDestroyed;

public:
	void CreateGameHUDs();
	void CreateGameHUD(UGameHUD* GameHUD);
	void ClearupGameHUDs();
	void RemoveGameHUD(UGameHUD* GameHUD);
	void RemoveGameHUD(FGameplayTag InTag);

	virtual TArray<UGameHUD*> GetGameHUDByTag(FGameplayTag InTag);
	virtual void SetGameHUDVisibility(bool IsVisisble);
	virtual void SetGameHUDVisibility(UGameHUD* GameHUD, bool IsVisisble);
	virtual void SetGameHUDVisibility(FGameplayTag InTag, bool IsVisisble);

protected:
	void AddTemporaryGameHUD(UUserWidgetBase* InWidget);
	void RemoveTemporaryGameHUD(UUserWidgetBase* InWidget);

	/* UGameplayTagSlot */
protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UGameplayTagSlot*> Slots;

protected:
	void RegisterSlot(UGameplayTagSlot* InSlot);
	void UnRegisterSlot(UGameplayTagSlot* InSlot);

public:
	UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag) const;
	void ClearupSlots();

	/* User Widget Base */
public:
	DECLARE_DELEGATE_OneParam(FOnWidgetActiveStateChanged, UUserWidgetBase*);

	virtual UUserWidgetBase* OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void OpenUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

	virtual void CloseUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void CloseUserWidget(FGameplayTag InSlotTag, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

protected:
	virtual void ActiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void ActiveWidget(UUserWidgetBase* InWidget, bool bIsInstant, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void InactiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void InactiveWidget(UUserWidgetBase* InWidget, bool bIsInstant, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

public:
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UUserWidgetBase*> ActivedWidgets;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserWidgetBaseDelegate, UUserWidgetBase*, UserWidgetBase);

	UPROPERTY(BlueprintAssignable)
	FUserWidgetBaseDelegate OnWidgetOpen;

	UPROPERTY(BlueprintAssignable)
	FUserWidgetBaseDelegate OnWidgetClose;

protected:
	UPROPERTY(Transient)
	TMap<UUserWidgetBase*, FTimerHandle> WidgetTimerHandles;

	/* Game Menu */
public:
	UPROPERTY(BlueprintReadOnly, Transient)
	UGameMenuSetting* GameMenu = nullptr;

	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FMenuGenerateInfo> MenuGenerateInfos;

public:
	virtual void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);
	virtual void SelectMenu(FGameplayTag InMenuTag);
	virtual void DeselectMenu(FGameplayTag InMenuTag);
	TArray<UMenuStyle*> GetMenuStyles();

protected:
	virtual void GenerateMenu(FGameplayTag InMenuTag);
	virtual void GenerateMenu(TArray<FGameplayTag> InMenuTags);
	virtual void DestroyMenu(FGameplayTag InMenuTag);
	virtual void DestroyMenu(TArray<FGameplayTag> InMenuTags);

protected:
	TMap<UMenuStyle*, bool> TargetMenuSelection;
	bool bProcessingMenuSelection = false;
	int32 ProcessingIndex = 0;

	virtual FReply OnMenuResponseStateChanged(UInteractableUserWidgetBase* InteractableWidget, bool TargetEventState);
	virtual void HandleMenuResponseStateChanged();
};
