// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MoveUserWidgetAsyncAction.generated.h"

class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UMoveUserWidgetAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (GameplayTagFilter="UI.HUD", BlueprintInternalUseOnly = "true"))
	static UMoveUserWidgetAsyncAction* AsyncMoveUserWidget(FGameplayTag OriginSlotTag, FGameplayTag TargetSlotTag);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserWidgetDelegate, UUserWidgetBase*, Widget);

	UPROPERTY(BlueprintAssignable)
	FUserWidgetDelegate OnFinish;

protected:
	virtual void OnHandleFinish(UUserWidgetBase* InWidget);
};
