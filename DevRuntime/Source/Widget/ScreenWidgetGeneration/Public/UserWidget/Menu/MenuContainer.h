// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "MenuContainer.generated.h"

class UMenuStyle;
class UCommonButtonGroupBase;

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UMenuContainer : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PreConstructMenuStyle(const TArray<FMenuInfo>& InMenuInfos);

	UFUNCTION(BlueprintImplementableEvent)
	void ConstructMenuStyle(UMenuStyle* InMenuStyle);

	UFUNCTION(BlueprintImplementableEvent)
	void PostConstructMenuStyle(const TArray<UMenuStyle*>& InMenuStyleArr);
};
