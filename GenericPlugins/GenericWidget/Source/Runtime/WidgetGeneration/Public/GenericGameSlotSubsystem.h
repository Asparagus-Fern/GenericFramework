// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WidgetType.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericGameSlotSubsystem.generated.h"

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
class UGenericGameSlotSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WIDGETGENERATION_API UGenericGameSlotSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* Delegate From UGenericWidgetSubsystem */
protected:
	virtual void PreWidgetOpened(FOpenWidgetParameter& Parameter);
	virtual void OnWidgetOpened(FOpenWidgetParameter& Parameter);
	virtual void PreWidgetClosed(FCloseWidgetParameter& Parameter);
	virtual void PostWidgetClosed(UGenericWidget* InWidget);

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
	WIDGETGENERATION_API virtual bool AddSlotWidget(UGenericWidget* InWidget);
	WIDGETGENERATION_API virtual void RemoveSlotWidget(UGenericWidget* InWidget);

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
