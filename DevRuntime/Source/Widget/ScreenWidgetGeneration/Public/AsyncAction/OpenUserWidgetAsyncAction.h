// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OpenUserWidgetAsyncAction.generated.h"

class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UOpenUserWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UOpenUserWidgetAsyncAction* AsyncOpenUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UOpenUserWidgetAsyncAction* AsyncOpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserWidgetDelegate, UUserWidgetBase*, Widget);

	UPROPERTY(BlueprintAssignable)
	FUserWidgetDelegate OnFinish;

protected:
	virtual void OnHandleFinish(UUserWidgetBase* InWidget);
};
