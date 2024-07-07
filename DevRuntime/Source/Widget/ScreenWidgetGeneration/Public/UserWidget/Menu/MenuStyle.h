// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Group/CommonButton.h"
#include "MenuStyle.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, HideCategories=(Interaction,Layout,Localization,Performance,Rendering,Navigation,Designer))
class SCREENWIDGETGENERATION_API UMenuStyle : public UCommonButton
{
	GENERATED_BODY()

	/* UMenuStyle */
public:
	UMenuStyle(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;
	virtual void NativeOnClicked() override;
	virtual void NativeOnSelected(bool bBroadcast) override;
	virtual void NativeOnDeselected(bool bBroadcast) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ConstructMenuStyle(FMenuInfo InMenuInfo);
	virtual void NativeConstructMenuStyle(FMenuInfo InMenuInfo);

public:
	UPROPERTY(Getter, BlueprintGetter="GetMenuInfo")
	FMenuInfo MenuInfo;

public:
	UFUNCTION(BlueprintPure)
	FMenuInfo GetMenuInfo() const;
};
