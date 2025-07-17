// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WidgetType.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericHUDManager.generated.h"

class UGenericWidget;
class UGenericHUD;
class UGameplayTagSlot;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSlotRegister, UGameplayTagSlot*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSlotRegister, UGameplayTagSlot*, InSlot);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSlotUnRegister, UGameplayTagSlot*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSlotUnRegister, UGameplayTagSlot*, InSlot);

DECLARE_MULTICAST_DELEGATE(FDelegate_HUDDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBPDelegate_HUDDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnHUDCreated, UGenericHUD*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnHUDCreated, UGenericHUD*, InHUD);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnHUDDestroyed, UGenericHUD*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnHUDDestroyed, UGenericHUD*, InHUD);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnHUDActiveStateChanged, UGenericHUD*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnHUDActiveStateChanged, UGenericHUD*, InHUD, bool, InActiveState);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericHUDManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* IStateInterface */
protected:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* Delegate From UWidgetManager */
private:
	void PreWidgetOpened(FOpenWidgetParameter& Parameter);
	void OnWidgetOpened(FOpenWidgetParameter& Parameter);
	void PreWidgetClosed(FCloseWidgetParameter& Parameter);
	void PostWidgetClosed(UGenericWidget* InWidget);

	/* UGameplayTagSlot */
public:
	WIDGETGENERATION_API void RegisterSlot(UGameplayTagSlot* InSlot);
	WIDGETGENERATION_API void UnRegisterSlot(UGameplayTagSlot* InSlot);

	WIDGETGENERATION_API UGameplayTagSlot* GetSlot(const UGenericWidget* InWidget) const;
	WIDGETGENERATION_API UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag) const;
	WIDGETGENERATION_API TArray<UGameplayTagSlot*> GetSlots() { return Slots; }

	WIDGETGENERATION_API UGenericWidget* GetSlotWidget(FGameplayTag InSlotTag) const;
	WIDGETGENERATION_API TArray<UGenericWidget*> GetSlotWidgets() const;

	WIDGETGENERATION_API bool AddSlotWidget(UGenericWidget* InWidget) const;
	WIDGETGENERATION_API bool RemoveSlotWidget(UGenericWidget* InWidget) const;

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
	WIDGETGENERATION_API void CreateGameHUDs(const TArray<TSoftClassPtr<UGenericHUD>>& InGameHUDClasses);
	WIDGETGENERATION_API void CreateGameHUDs(TArray<TSubclassOf<UGenericHUD>> InGameHUDClasses);
	WIDGETGENERATION_API void CreateGameHUDs(TArray<UGenericHUD*> InGameHUDs);
	WIDGETGENERATION_API void CreateGameHUD(UGenericHUD* InGameHUD);

	WIDGETGENERATION_API void RemoveGameHUDs(TArray<FGameplayTag> InHUDTags);
	WIDGETGENERATION_API void RemoveGameHUD(FGameplayTag InHUDTag);
	WIDGETGENERATION_API void RemoveGameHUDs(TArray<UGenericHUD*> InGameHUDs);
	WIDGETGENERATION_API void RemoveGameHUD(UGenericHUD* InGameHUD);

	WIDGETGENERATION_API void ClearGameHUDs();

	/* 从标签查找HUD */
	WIDGETGENERATION_API UGenericHUD* GetGameHUDByTag(FGameplayTag InHUDTag) const;

	/* 从标签查找所有匹配的HUD */
	WIDGETGENERATION_API TArray<UGenericHUD*> GetGameHUDsByTag(FGameplayTag InHUDTag);

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
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UGenericHUD>> GameHUDs;
};
