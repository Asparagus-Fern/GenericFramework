// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Group/CommonButton.h"
#include "UserWidget/Base/UserWidgetInterface.h"
#include "MenuStyle.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, HideCategories=(Interaction,Layout,Localization,Performance,Rendering,Navigation,Designer))
class SCREENWIDGETGENERATION_API UMenuStyle : public UCommonButton, public IUserWidgetInterface
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

	/* IUserWidgetInterface */
public:
	virtual void NativeOnOpen() override;
	virtual void NativeOnClose() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;

public:
	UPROPERTY(BlueprintReadOnly)
	FMenuInfo MenuInfo;
};
