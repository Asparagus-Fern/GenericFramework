// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Group/CommonButton.h"
#include "MenuStyle.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, HideCategories=(Interaction,Layout,Localization,Performance,Rendering,Navigation,Designer))
class SCREENWIDGETGENERATION_API UMenuStyle : public UCommonButton
{
	GENERATED_BODY()

	/* UCommonButtonBase */
public:
	UMenuStyle(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;
	virtual void NativeOnClicked() override;
	virtual void NativeOnSelected(bool bBroadcast) override;
	virtual void NativeOnDeselected(bool bBroadcast) override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UMenuStyle */
public:
	UPROPERTY(Getter, BlueprintGetter="GetMenuInfo")
	FMenuInfo MenuInfo;

public:
	UFUNCTION(BlueprintPure)
	FMenuInfo GetMenuInfo() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ConstructMenuStyle(FMenuInfo InMenuInfo);
	virtual void NativeConstructMenuStyle(FMenuInfo InMenuInfo);
};
