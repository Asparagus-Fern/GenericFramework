// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableUserWidgetBase.h"
#include "UserWidgetBaseGroup.generated.h"

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UUserWidgetBaseGroup : public UInteractableUserWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveWidget(UUserWidgetBase* InWidget);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UUserWidgetBase*> UserWidgets;
};
