// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UWidget/Override/GameplayTagSlot.h"
// #include "WidgetDelegate.generated.h"

class UUserWidgetBase;

DECLARE_DELEGATE_OneParam(FOnWidgetActiveStateChanged, UUserWidgetBase*);

struct FWidgetDelegate
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetActualOpened, UUserWidgetBase*)
	inline static FOnWidgetActualOpened OnWidgetActualOpened;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetActualClosed, UUserWidgetBase*)
	inline static FOnWidgetActualClosed OnWidgetActualClosed;
};

struct FWidgetHUDDelegate
{
	DECLARE_DELEGATE_RetVal_OneParam(UGameplayTagSlot*, FGetGameplayTagSlot, UUserWidgetBase*)
	inline static FGetGameplayTagSlot RequestGameplayTagSlot;

	DECLARE_DELEGATE_RetVal_OneParam(UUserWidgetBase*, FGetGameplayTagSlotWidget, FGameplayTag)
	inline static FGetGameplayTagSlotWidget RequestGameplayTagSlotWidget;

	DECLARE_DELEGATE_RetVal_OneParam(bool, FAddGameplayTagSlotWidget, UUserWidgetBase*)
	inline static FAddGameplayTagSlotWidget RequestAddGameplayTagSlotWidget;

	DECLARE_DELEGATE_RetVal_OneParam(bool, FRemoveGameplayTagSlotWidget, UUserWidgetBase*)
	inline static FRemoveGameplayTagSlotWidget RequestRemoveGameplayTagSlotWidget;
};
