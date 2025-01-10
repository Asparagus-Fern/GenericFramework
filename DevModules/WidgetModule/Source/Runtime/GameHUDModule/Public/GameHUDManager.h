// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameHUDManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEHUDMODULE_API UGameHUDManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	/* UGameplayTagSlot */
public:
	DECLARE_EVENT_OneParam(UScreenWidgetManager, FSlotDelegate, UGameplayTagSlot*);

	static FSlotDelegate OnSlotRegister;
	static FSlotDelegate OnSlotUnRegister;
	static FScreenWidgetDelegate OnSlslotClearup;

public:
	void RegisterSlot(UGameplayTagSlot* InSlot);
	void UnRegisterSlot(UGameplayTagSlot* InSlot);
	void ClearupSlots();

	UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag) const;
	UUserWidgetBase* GetSlotWidget(FGameplayTag InSlotTag);

private:
	/* 当前视口所有以注册的插槽 */
	UPROPERTY(BlueprintReadOnly, Transient)
	TArray<TObjectPtr<UGameplayTagSlot>> Slots;
};
