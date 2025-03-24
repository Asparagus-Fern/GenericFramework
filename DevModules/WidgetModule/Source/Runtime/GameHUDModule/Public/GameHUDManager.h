// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameHUDManager.generated.h"

class UUserWidgetBase;
class UGameHUD;
class UGameplayTagSlot;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSlotRegister, UGameplayTagSlot*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSlotRegister, UGameplayTagSlot*, InSlot);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSlotUnRegister, UGameplayTagSlot*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSlotUnRegister, UGameplayTagSlot*, InSlot);

DECLARE_MULTICAST_DELEGATE(FDelegate_HUDDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBPDelegate_HUDDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnHUDCreated, UGameHUD*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnHUDCreated, UGameHUD*, InHUD);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnHUDDestroyed, UGameHUD*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnHUDDestroyed, UGameHUD*, InHUD);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnHUDActiveStateChanged, UGameHUD*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnHUDActiveStateChanged, UGameHUD*, InHUD, bool, InActiveState);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGameHUDManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

protected:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* Delegate From WidgetManager */
private:
	void PreWidgetOpened(UUserWidgetBase* InWidget);
	void PostWidgetClosed(UUserWidgetBase* InWidget);

	/* UGameplayTagSlot */
public:
	GAMEHUDMODULE_API void RegisterSlot(UGameplayTagSlot* InSlot);
	GAMEHUDMODULE_API void UnRegisterSlot(UGameplayTagSlot* InSlot);

	GAMEHUDMODULE_API UGameplayTagSlot* GetSlot(UUserWidgetBase* InWidget) const;
	GAMEHUDMODULE_API UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag) const;
	GAMEHUDMODULE_API TArray<UGameplayTagSlot*> GetSlots() { return Slots; }

	GAMEHUDMODULE_API UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag) const;
	GAMEHUDMODULE_API TArray<UUserWidgetBase*> GetSlotWidgets() const;

	GAMEHUDMODULE_API bool AddSlotWidget(UUserWidgetBase* InWidget);
	GAMEHUDMODULE_API bool RemoveSlotWidget(UUserWidgetBase* InWidget);

public:
	inline static FDelegate_OnSlotRegister Delegate_OnSlotRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnSlotRegister BPDelegate_OnSlotRegister;

	inline static FDelegate_OnSlotUnRegister Delegate_OnSlotUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnSlotUnRegister BPDelegate_OnSlotUnRegister;

protected:
	/* 当前视口所有已注册的插槽 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UGameplayTagSlot>> Slots;

	/* Game HUD */
public:
	GAMEHUDMODULE_API void CreateGameHUDs(TArray<TSoftClassPtr<UGameHUD>> InGameHUDClasses, bool bAddToViewport = true);
	GAMEHUDMODULE_API void CreateGameHUDs(TArray<TSubclassOf<UGameHUD>> InGameHUDClasses, bool bAddToViewport = true);
	GAMEHUDMODULE_API void CreateGameHUDs(TArray<UGameHUD*> InGameHUDs, bool bAddToViewport = true);
	GAMEHUDMODULE_API void CreateGameHUD(UGameHUD* InGameHUD, bool bAddToViewport = true);

	GAMEHUDMODULE_API void RemoveGameHUDs(TArray<UGameHUD*> InGameHUDs);
	GAMEHUDMODULE_API void RemoveGameHUD(UGameHUD* InGameHUD);
	GAMEHUDMODULE_API void RemoveGameHUDs(TArray<FGameplayTag> InHUDTags);
	GAMEHUDMODULE_API void RemoveGameHUD(FGameplayTag InHUDTag);

	GAMEHUDMODULE_API void ClearupGameHUDs();

	/* 从标签查找HUD */
	GAMEHUDMODULE_API UGameHUD* GetGameHUDByTag(FGameplayTag InHUDTag);

	/* 从标签查找所有匹配的HUD */
	GAMEHUDMODULE_API TArray<UGameHUD*> GetGameHUDsByTag(FGameplayTag InHUDTag);

	/* 设置所有HUD的显隐 */
	GAMEHUDMODULE_API void SetAllGameHUDActiveState(bool IsActived);

	/* 设置指定HUD的显隐 */
	GAMEHUDMODULE_API void SetGameHUDActiveState(UGameHUD* InGameHUD, bool IsActived) const;

	/* 从标签查找HUD并设置显隐 */
	GAMEHUDMODULE_API void SetGameHUDActiveState(FGameplayTag InTag, bool IsActived);

	/* 创建该Widget的临时HUD，在移除该Widget时将，如果其他Widget没有使用到该临时HUD，将被移除 */
	GAMEHUDMODULE_API void AddTemporaryGameHUD(UUserWidgetBase* InWidget);

	/* 移除该Widget的临时HUD，如果有其他Widget正在使用该临时HUD，将不被移除 */
	GAMEHUDMODULE_API void RemoveTemporaryGameHUD(UUserWidgetBase* InWidget);

protected:
	TArray<TSubclassOf<UGameHUD>> GetCurrentGameHUDClasses();

public:
	inline static FDelegate_HUDDelegate Delegate_PreHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_HUDDelegate BPDelegate_PreHUDCreated;

	inline static FDelegate_OnHUDCreated Delegate_OnHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDCreated BPDelegate_OnHUDCreated;

	inline static FDelegate_HUDDelegate Delegate_PostHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_HUDDelegate BPDelegate_PostHUDCreated;

	inline static FDelegate_OnHUDDestroyed Delegate_OnHUDDestroyed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDDestroyed BPDelegate_OnHUDDestroyed;

	inline static FDelegate_OnHUDActiveStateChanged Delegate_OnHUDActiveStateChanged;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDActiveStateChanged BPDelegate_OnHUDActiveStateChanged;

protected:
	/* 当前视口所有创建的HUD */
	UPROPERTY(Transient, BlueprintReadOnly)
	TArray<TObjectPtr<UGameHUD>> GameHUDs;
};
