// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetType.h"
#include "Manager/CoreManager.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "ScreenWidgetManager.generated.h"

class UShortcutWidgetHandle;
class UCommonButtonBase;
class UInstanceUserWidgetBase;
class UGameplayTagSlot;
class UGameWidgetSetting;
class UGameLoading;
class UGameHUD;
class UGameMenuSetting;
class UUserWidgetBase;

DECLARE_DELEGATE_OneParam(FOnWidgetActiveStateChanged, UUserWidgetBase*);

/**
 * 处理UMG的动画过渡
 */
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
	DECLARE_EVENT(UScreenWidgetManager, FScreenWidgetDelegate);

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
	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnInteractableWidgetAdded, UInteractableUserWidgetBase*, FString);

	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnInteractableWidgetRemoved, UInteractableUserWidgetBase*, FString);

	DECLARE_EVENT_OneParam(UScreenWidgetManager, FOnInteractableWidgetClearup, FString);

	static FOnInteractableWidgetAdded OnInteractableWidgetAdded;
	static FOnInteractableWidgetRemoved OnInteractableWidgetRemoved;
	static FOnInteractableWidgetClearup OnInteractableWidgetClearup;

	virtual void AddInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);
	virtual void RemoveInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName);
	virtual void ClearupInteractableWidgetGroup(const FString& GroupName, bool DeselectAll);
	virtual bool FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const;

public:
	/* 当前管理的所有按钮组 */
	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<FString, TObjectPtr<UCommonButtonGroup>> InteractableWidgetGroups;

	/* Game HUD */
public:
	/* 当前视口所有创建的HUD */
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<TObjectPtr<UGameHUD>> GameHUDs;

private:
	bool bIsHUDCreated = false;

public:
	DECLARE_EVENT_OneParam(UScreenWidgetManager, FHUDDelegate, UGameHUD*);

	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnHUDActiveStateChanged, UGameHUD*, bool);

	static FScreenWidgetDelegate PreHUDCreated;
	static FHUDDelegate OnHUDCreated;
	static FScreenWidgetDelegate PostHUDCreated;
	static FScreenWidgetDelegate PreHUDDestroyed;
	static FHUDDelegate OnHUDDestroyed;
	static FScreenWidgetDelegate PostHUDDestroyed;

	static FOnHUDActiveStateChanged OnHUDActiveStateChanged;

public:
	void CreateGameHUDs(TArray<TSoftClassPtr<UGameHUD>> InGameHUDClasses, bool bAddToViewport = true);
	void CreateGameHUDs(TArray<TSubclassOf<UGameHUD>> InGameHUDClasses, bool bAddToViewport = true);
	void CreateGameHUDs(TArray<UGameHUD*> InGameHUDs, bool bAddToViewport = true);
	void CreateGameHUD(UGameHUD* GameHUD, bool bAddToViewport = true);
	void ClearupGameHUDs();
	void RemoveGameHUD(UGameHUD* GameHUD);
	void RemoveGameHUD(FGameplayTag InTag);

	/* 从标签查找HUD */
	virtual TArray<UGameHUD*> GetGameHUDByTag(FGameplayTag InTag);

	/* 设置所有HUD的显隐 */
	virtual void SetGameHUDActiveState(bool IsActived);

	/* 设置指定HUD的显隐 */
	virtual void SetGameHUDActiveState(UGameHUD* GameHUD, bool IsActived);

	/* 从标签查找HUD并设置显隐 */
	virtual void SetGameHUDActiveState(FGameplayTag InTag, bool IsActived);

	bool IsGameHUDCreated() const { return bIsHUDCreated; }

protected:
	/* 创建该Widget的临时HUD，在移除该Widget时将，如果其他Widget没有使用到该临时HUD，将被移除 */
	void AddTemporaryGameHUD(UUserWidgetBase* InWidget);

	/* 移除该Widget的临时HUD，如果有其他Widget正在使用该临时HUD，将不被移除 */
	void RemoveTemporaryGameHUD(UUserWidgetBase* InWidget);

	/* UGameplayTagSlot */
public:
	DECLARE_EVENT_OneParam(UScreenWidgetManager, FSlotDelegate, UGameplayTagSlot*);

	static FSlotDelegate OnSlotRegister;
	static FSlotDelegate OnSlotUnRegister;
	static FScreenWidgetDelegate OnSlslotClearup;

public:
	/* 当前视口所有以注册的插槽 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UGameplayTagSlot>> Slots;

public:
	void RegisterSlot(UGameplayTagSlot* InSlot);
	void UnRegisterSlot(UGameplayTagSlot* InSlot);
	void ClearupSlots();

	UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag) const;
	UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag);

	/* User Widget Base */
public:
	static UUserWidgetBase* GetContainerWidget(const FWidgetContainer& WidgetContainer);

public:
	DECLARE_EVENT_OneParam(UScreenWidgetManager, FUserWidgetBaseDelegate, UUserWidgetBase*);

	static FUserWidgetBaseDelegate OnWidgetOpen;
	static FUserWidgetBaseDelegate OnWidgetClose;

public:
	virtual UUserWidgetBase* OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual bool OpenUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

	virtual bool CloseUserWidget(FGameplayTag InSlotTag, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged(), bool MarkAsGarbage = true);
	virtual bool CloseUserWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged(), bool MarkAsGarbage = true);

	virtual void MoveUserWidget(FGameplayTag OriginSlotTag, FGameplayTag TargetSlotTag, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());

protected:
	virtual void ActiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void ActiveWidget(UUserWidgetBase* InWidget, bool bIsInstant, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	virtual void InactiveWidget(UUserWidgetBase* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged(), bool MarkAsGarbage = true);
	virtual void InactiveWidget(UUserWidgetBase* InWidget, bool bIsInstant, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged(), bool MarkAsGarbage = true);

	virtual FTimerHandle PlayWidgetAnimation(UUserWidgetBase* InWidget, bool InIsActive, FTimerDelegate const& InDelegate);

public:
	/* 当前显示在屏幕上的所有UI */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UUserWidgetBase>> ActivedWidgets;

protected:
	UPROPERTY(Transient)
	TArray<FWidgetAnimationTimerHandle> WidgetAnimationTimerHandles;

	/* Game Menu */
public:
	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnMenuSelectionChanged, FGameplayTag, bool)

	static FOnMenuSelectionChanged OnMenuSelectionChanged;

public:
	/* 当前菜单数据 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<UGameMenuSetting> GameMenu = nullptr;

	/* 所有由菜单数据创建的已被指定Style和Container的菜单 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<FMenuGenerateInfo> MenuGenerateInfos;

public:
	virtual void SwitchGameMenu(UGameMenuSetting* InGameMenuSetting);
	virtual void SelectMenu(FGameplayTag InMenuTag);
	virtual void DeselectMenu(FGameplayTag InMenuTag);

protected:
	/* 是否需要清理生成信息 */
	bool bClearupMenuGenerateInfos = false;

	/* 是否正在切换菜单数据 */
	bool bSwitchingGameMenu = false;

	/* 等待切换的菜单数据 */
	UPROPERTY(Transient)
	TObjectPtr<UGameMenuSetting> WaitingGameMenu = nullptr;

	UPROPERTY(Transient)
	TMap<UMenuStyle*, bool> TargetMenuSelection;

	bool bProcessingMenuSelection = false;
	int32 ProcessingMenuIndex = 0;

protected:
	TArray<UMenuStyle*> GetMenuStyles();

	virtual void GenerateMenu(FGameplayTag InMenuTag);
	virtual void GenerateMenu(TArray<FGameplayTag> InMenuTags);
	virtual void DestroyMenu(FGameplayTag InMenuTag);
	virtual void DestroyMenu(TArray<FGameplayTag> InMenuTags);

	virtual FReply OnMenuResponseStateChanged(UInteractableUserWidgetBase* InteractableWidget, bool TargetEventState);
	virtual void HandleMenuResponseStateChanged();

	/* Shortcut Widget */
protected:
	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<UDataTable> ShortcutWidgetTable = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UShortcutWidgetHandle>> ShortcutWidgetHandles;

protected:
	void RegisterShortcutWidgetHandles();
	void UnRegisterShortcutWidgetHandles();
	UShortcutWidgetHandle* GetShortcutWidgetHandle(const UUserWidgetBase* InWidget);
	UShortcutWidgetHandle* GetShortcutWidgetHandle(TSubclassOf<UUserWidgetBase> InWidgetClass);
};
