// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UserWidgetInterface.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget/Base/UserWidgetType.h"
#include "UserWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideCategories=(Appearance,Input,Interaction,Layout,Localization,Performance,Rendering,Navigation,Designer))
class SCREENWIDGETGENERATION_API UUserWidgetBase : public UUserWidget, public IUserWidgetInterface
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="HUD"))
	FGameplayTag SlotTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ZOrder = 0;

	/* IUserWidgetInterface */
public:
	virtual void NativeOnOpen() override;
	virtual void NativeOnClose() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
};
