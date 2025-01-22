// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableWidgetBase.h"
#include "MenuStyle.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MENUGENERATION_API UMenuStyle : public UInteractableWidgetBase
{
	GENERATED_BODY()

public:
	// UPROPERTY(Getter, BlueprintGetter="GetMenuContainer")
	// UMenuContainer* MenuContainer = nullptr;
	//
	// UPROPERTY(Getter, BlueprintGetter="GetMenuInfo")
	// FMenuInfo MenuInfo;

public:
	// UFUNCTION(BlueprintNativeEvent)
	// void PreConstructMenuStyle(FMenuInfo InMenuInfo);
	// virtual void NativePreConstructMenuStyle(FMenuInfo InMenuInfo);
	//
	// UFUNCTION(BlueprintNativeEvent)
	// void ConstructMenuStyle(FMenuInfo InMenuInfo);
	// virtual void NativeConstructMenuStyle(FMenuInfo InMenuInfo);

public:
	// UFUNCTION(BlueprintPure)
	// UMenuContainer* GetMenuContainer() const { return MenuContainer; }
	//
	// UFUNCTION(BlueprintPure)
	// FMenuInfo GetMenuInfo() const { return MenuInfo; }
	//
	// UFUNCTION(BlueprintPure)
	// FGameplayTag GetMenuTag() const { return MenuInfo.MenuTag; }
};
