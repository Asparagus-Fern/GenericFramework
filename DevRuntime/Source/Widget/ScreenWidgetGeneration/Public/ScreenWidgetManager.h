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

DECLARE_DELEGATE_OneParam(FOnWidgetActiveStateChanged, UUserWidgetBase*);

USTRUCT()
struct FWidgetAnimationTimerHandle
{
	GENERATED_BODY()

public:
	FWidgetAnimationTimerHandle();
	FWidgetAnimationTimerHandle(FTimerHandle InTimerHandle, UUserWidgetBase* InWidget, const FOnWidgetActiveStateChanged& Finish);

	bool operator==(const FWidgetAnimationTimerHandle& Other) const;
	bool operator==(const UUserWidgetBase* OtherWidget) const;

public:
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	UUserWidgetBase* Widget = nullptr;

public:
	FOnWidgetActiveStateChanged OnFinish;
};

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UScreenWidgetManager : public UCoreManager
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnRefresh() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* UCoreManager */
public:
	virtual void OnWorldMatchStarting_Implementation() override;

	/* Interactable Widget Group */
public:
	virtual void AddInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);
	virtual void RemoveInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);
	virtual void ClearupInteractableWidgetGroup(const FString& GroupName, bool DeselectAll);
	virtual bool FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const;

public:
	/* 当前管理的所有按钮组 */
	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<FString, UCommonButtonGroup*> InteractableWidgetGroups;

	/* Game HUD */
public:
	/* 当前视口所有创建的HUD */
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<UGameHUD*> GameHUDs;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScreenWidgetDelegate);

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
	void CreateGameHUD(UGameHUD* GameHUD, bool bAddToViewport = true);
	void ClearupGameHUDs();
	void RemoveGameHUD(UGameHUD* GameHUD);
	void RemoveGameHUD(FGameplayTag InTag);

	virtual TArray<UGameHUD*> GetGameHUDByTag(FGameplayTag InTag);

	/* 设置所有HUD的显隐 */
	virtual void SetGameHUDActiveState(bool IsActived);

	/* 设置指定HUD的显隐 */
	virtual void SetGameHUDActiveState(UGameHUD* GameHUD, bool IsActived);

	/* 从标签查找HUD并设置显隐 */
	virtual void SetGameHUDActiveState(FGameplayTag InTag, bool IsActived);

protected:
	/* 创建该Widget的临时HUD，在移除该Widget时将，如果其他Widget没有使用到该临时HUD，将被移除 */
	void AddTemporaryGameHUD(UUserWidgetBase* InWidget);

	/* 移除该Widget的临时HUD，如果有其他Widget正在使用该临时HUD，将不被移除 */
	void RemoveTemporaryGameHUD(UUserWidgetBase* InWidget);

	/* UGameplayTagSlot */
public:
	/* 当前视口所有以注册的插槽 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<UGameplayTagSlot*> Slots;

public:
	UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag) const;
	UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag);
	void ClearupSlots();

protected:
	void RegisterSlot(UGameplayTagSlot* InSlot);
	void UnRegisterSlot(UGameplayTagSlot* InSlot);

	/* User Widget Base */
public:
	static UUserWidgetBase* GetContainerWidget(const FWidgetContainer& WidgetContainer);

public:
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
	/* 当前显示在屏幕上的所有UI */
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
	TArray<FWidgetAnimationTimerHandle> WidgetAnimationTimerHandles;

	/* Game Menu */
public:
	/* 当前菜单数据 */
	UPROPERTY(BlueprintReadOnly, Transient)
	UGameMenuSetting* GameMenu = nullptr;

	/* 所有由菜单数据创建的已被指定Style和Container的菜单 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FMenuGenerateInfo> MenuGenerateInfos;

public:
	virtual void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);
	virtual void SelectMenu(FGameplayTag InMenuTag);
	virtual void DeselectMenu(FGameplayTag InMenuTag);

protected:
	virtual void GenerateMenu(FGameplayTag InMenuTag);
	virtual void GenerateMenu(TArray<FGameplayTag> InMenuTags);
	virtual void DestroyMenu(FGameplayTag InMenuTag);
	virtual void DestroyMenu(TArray<FGameplayTag> InMenuTags);

	TArray<UMenuStyle*> GetMenuStyles();

protected:
	TMap<UMenuStyle*, bool> TargetMenuSelection;
	bool bProcessingMenuSelection = false;
	int32 ProcessingIndex = 0;

	virtual FReply OnMenuResponseStateChanged(UInteractableUserWidgetBase* InteractableWidget, bool TargetEventState);
	virtual void HandleMenuResponseStateChanged();
};
