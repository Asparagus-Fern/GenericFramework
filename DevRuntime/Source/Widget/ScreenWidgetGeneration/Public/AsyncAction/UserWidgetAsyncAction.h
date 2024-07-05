// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UserWidgetAsyncAction.generated.h"

class UUserWidgetBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUserWidgetDelegate);

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UUserWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UUserWidgetAsyncAction* AsyncOpenUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UUserWidgetAsyncAction* AsyncOpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass, UUserWidgetBase*& NewWidget);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UUserWidgetAsyncAction* AsyncCloseUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UUserWidgetAsyncAction* AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag);

public:
	UPROPERTY(BlueprintAssignable)
	FUserWidgetDelegate OnFinish;

protected:
	virtual void OnHandleFinish();
};
