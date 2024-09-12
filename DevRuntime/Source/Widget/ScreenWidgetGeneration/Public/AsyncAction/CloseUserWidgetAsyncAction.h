// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CloseUserWidgetAsyncAction.generated.h"

class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCloseUserWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AdvancedDisplay = 1))
	static UCloseUserWidgetAsyncAction* AsyncCloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AdvancedDisplay = 1))
	static UCloseUserWidgetAsyncAction* AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage = true);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUserWidgetDelegate);

	UPROPERTY(BlueprintAssignable)
	FUserWidgetDelegate OnFinish;

protected:
	virtual void OnHandleFinish(UUserWidgetBase* InWidget);
};
