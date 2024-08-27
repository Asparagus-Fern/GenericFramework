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
	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UCloseUserWidgetAsyncAction* AsyncCloseUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UCloseUserWidgetAsyncAction* AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUserWidgetDelegate);

	UPROPERTY(BlueprintAssignable)
	FUserWidgetDelegate OnFinish;

protected:
	virtual void OnHandleFinish(UUserWidgetBase* InWidget);
};
