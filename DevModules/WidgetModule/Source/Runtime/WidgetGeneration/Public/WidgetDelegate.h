// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
