// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableWidgetBase.h"
#include "MenuStyle.generated.h"

class UMenuEntityBase;

/**
 * 
 */
UCLASS(BlueprintType)
class MENUGENERATION_API UMenuStyle : public UInteractableWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ConstructMenuStyle();
	virtual void NativeConstructMenuStyle();

	UFUNCTION(BlueprintPure)
	UMenuEntityBase* GetMenuEntityBase() const;
};
