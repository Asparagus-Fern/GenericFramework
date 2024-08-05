// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Blueprint/UserWidget.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "UserWidgetBase.generated.h"

class UWidgetAnimationEvent;

/**
 * 
 */
UCLASS(Abstract, HideCategories=(Performance,Localization))
class SCREENWIDGETGENERATION_API UUserWidgetBase : public UUserWidget
                                                   , public IProcedureInterface
                                                   , public IWidgetAnimationInterface
{
	GENERATED_UCLASS_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "UserCreate", "User Widget Base"); }
#endif
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;

	/* UUserWidgetBase */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag SelfTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="HUD"))
	FGameplayTag SlotTag;

	/* IWidgetAnimationInterface */
public:
	virtual bool HasAnimationEvent_Implementation() const override;
	virtual UWidgetAnimationEvent* GetActiveAnimationEvent_Implementation() const override;
	virtual void SetActiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual UWidgetAnimationEvent* GetInactiveAnimationEvent_Implementation() const override;
	virtual void SetInactiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual void PlayAnimationEvent_Implementation(bool InIsActive) override;

public:
	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* ActiveAnimationEvent = nullptr;

	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* InactiveAnimationEvent = nullptr;
};
