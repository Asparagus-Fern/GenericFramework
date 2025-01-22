// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OpenUserWidgetAsyncAction.generated.h"

class UUserWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenUserWidgetDelegate, UUserWidgetBase*, Widget);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserWidgetActivedAnimationDelegate);

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UOpenUserWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UOpenUserWidgetAsyncAction* AsyncOpenUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UOpenUserWidgetAsyncAction* AsyncOpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass);

public:
	UPROPERTY(BlueprintAssignable)
	FOpenUserWidgetDelegate OnFinish;

	UPROPERTY(BlueprintAssignable)
	FOnUserWidgetActivedAnimationDelegate OnAnimationFinish;

private:
	virtual void OnWidgetActived(UUserWidgetBase* InWidget);
	virtual void OnWidgetActivedAnimationFinish(UUserWidgetBase* InWidget, bool InIsActived);
};
