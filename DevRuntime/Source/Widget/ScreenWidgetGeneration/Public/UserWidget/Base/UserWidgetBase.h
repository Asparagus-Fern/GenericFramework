// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
class SCREENWIDGETGENERATION_API UUserWidgetBase : public UUserWidget, public IProcedureInterface, public IProcedureBaseInterface
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

	/* Widget Animation */
public:
	UPROPERTY(EditAnywhere, Instanced, Getter, Setter, BlueprintGetter="GetAnimationEvent", BlueprintSetter="SetAnimationEvent")
	UWidgetAnimationEvent* AnimationEvent = nullptr;

	UFUNCTION(BlueprintPure)
	UWidgetAnimationEvent* GetAnimationEvent() const;

	UFUNCTION(BlueprintCallable)
	void SetAnimationEvent(UWidgetAnimationEvent* InAnimationEvent);

	UFUNCTION(BlueprintPure)
	bool HasAnimationEvent() const;

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
