// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScreenWidgetType.h"
#include "Manager/TickableInternalManager.h"
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

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UScreenWidgetManager : public UWorldSubsystem, public FTickableInternalManager
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(UScreenWidgetManager, FScreenWidgetDelegate);

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FTickableGameObject */
public:
	virtual bool IsTickable() const override { return true; }
	virtual void Tick(float DeltaTime) override;

	/* FCoreInternalManager */
public:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* Game Menu */
public:
	DECLARE_EVENT_TwoParams(UScreenWidgetManager, FOnMenuSelectionChanged, FGameplayTag, bool)

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMenuSelectionChanged_BP, FGameplayTag, InTag, bool, bSelection);

	static FOnMenuSelectionChanged OnMenuSelectionChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMenuSelectionChanged_BP BPDelegate_OnMenuSelectionChanged;

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
	TArray<FGameplayTag> SelectedMenuCache;

	FDelegateHandle SelectMenuRecursiveHandle;
	void HandleSelectMenuRecursive(FGameplayTag MenuTag, bool IsSelected);

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

	virtual FReply OnMenuResponseStateChanged(UInteractableWidgetBase* InteractableWidget, bool TargetEventState);
	virtual void HandleMenuResponseStateChanged();
};
