// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CloseUserWidgetAsyncAction.generated.h"

class UUserWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseUserWidgetDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserWidgetInactivedAnimationDelegate);

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UCloseUserWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AdvancedDisplay = 1))
	static UCloseUserWidgetAsyncAction* AsyncCloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable, meta = (GameplayTagFilter="UI.HUD", BlueprintInternalUseOnly = "true", AdvancedDisplay = 1))
	static UCloseUserWidgetAsyncAction* AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage = true);

public:
	UPROPERTY(BlueprintAssignable)
	FOnUserWidgetInactivedAnimationDelegate OnAnimationFinish;

	UPROPERTY(BlueprintAssignable)
	FCloseUserWidgetDelegate OnFinish;

private:
	virtual void OnWidgetInactived(UUserWidgetBase* InWidget);
	virtual void OnWidgetInactivedAnimationFinish(UUserWidgetBase* InWidget, bool InIsActived);
};
