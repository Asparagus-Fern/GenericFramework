// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Blueprint/UserWidget.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "UserWidget/Base/UserWidgetType.h"
#include "UserWidgetBase.generated.h"

class UWidgetAnimationEvent;


/**
 * 
 */
UCLASS(Abstract, HideCategories=(Appearance,Input,Interaction,Layout,Localization,Performance,Navigation,Designer))
class SCREENWIDGETGENERATION_API UUserWidgetBase : public UUserWidget
                                                   , public IProcedureInterface
                                                   , public IWidgetAnimationInterface
{
	GENERATED_UCLASS_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "UserCreate", "User Widget Base"); }
#endif

public:
	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetSelfTag", meta=(Categories="UMG"))
	FGameplayTag SelfTag;

	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetSlotTag", meta=(Categories="HUD"))
	FGameplayTag SlotTag;

public:
	UFUNCTION(BlueprintPure)
	FGameplayTag GetSelfTag() const;

	UFUNCTION(BlueprintPure)
	FGameplayTag GetSlotTag() const;

	/* IWidgetAnimationInterface */
public:
	virtual UWidgetAnimationEvent* GetAnimationEvent_Implementation() const override;
	virtual void SetAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual bool HasAnimationEvent_Implementation() const override;
	virtual void PlayAnimationEvent_Implementation(bool InIsActive) override;

public:
	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* AnimationEvent = nullptr;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;
	virtual void NativeOnRefresh() override;
};
