// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WidgetType.h"
#include "Interface/ManagerInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericGameSlotManager.generated.h"

class UGenericWidget;
class UGameplayTagSlot;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSlotRegister, UGameplayTagSlot*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSlotRegister, UGameplayTagSlot*, InSlot);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSlotUnRegister, UGameplayTagSlot*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSlotUnRegister, UGameplayTagSlot*, InSlot);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericGameSlotManager : public UWorldSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

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

protected:
	WIDGETGENERATION_API bool AddSlotWidget(UGenericWidget* InWidget) const;
	WIDGETGENERATION_API void RemoveSlotWidget(UGenericWidget* InWidget) const;

public:
	WIDGETGENERATION_API inline static FDelegate_OnSlotRegister Delegate_OnSlotRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnSlotRegister BPDelegate_OnSlotRegister;

	WIDGETGENERATION_API inline static FDelegate_OnSlotUnRegister Delegate_OnSlotUnRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnSlotUnRegister BPDelegate_OnSlotUnRegister;

protected:
	/* 当前视口所有已注册的插槽 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UGameplayTagSlot>> Slots;
};


class WIDGETGENERATION_API FGameSlotHelper
{
public:
	static void RegisterSlot(UGameplayTagSlot* InSlot);
	static void UnRegisterSlot(UGameplayTagSlot* InSlot);

	static UGameplayTagSlot* GetSlot(const UGenericWidget* InWidget);
	static UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag);
	static TArray<UGameplayTagSlot*> GetSlots();

	static UGenericWidget* GetSlotWidget(FGameplayTag InSlotTag);
	static TArray<UGenericWidget*> GetSlotWidgets();
};
