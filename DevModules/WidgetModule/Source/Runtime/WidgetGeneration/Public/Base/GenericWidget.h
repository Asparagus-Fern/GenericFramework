// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "WidgetType.h"
#include "Runtime/WidgetGeneration/Public/Interface/WidgetAnimationInterface.h"
#include "Blueprint/UserWidget.h"
#include "Interface/StateInterface.h"
#include "Interface/WidgetChildrenInterface.h"
#include "GenericWidget.generated.h"

class UCommonUISubsystemBase;
class UCommonInputSubsystem;
class UGenericHUD;
class UCommonButton;
class UWidgetAnimationEvent;

/**
 * 
 */
UCLASS(Abstract)
class WIDGETGENERATION_API UGenericWidget : public UCommonUserWidget, public IWidgetAnimationInterface, public IStateInterface, public IWidgetChildrenInterface
{
	GENERATED_BODY()

protected:
	UGenericWidget(const FObjectInitializer& ObjectInitializer);
	virtual void OnWidgetRebuilt() override;
	virtual bool Initialize() override;
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "DevUserWidget", "User Widget Base"); }
#endif

	/* ==================== UGenericWidget ==================== */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI"))
	FGameplayTag SelfTag = FGameplayTag::EmptyTag;

	/* Unique Tag To Mark Which Slot To Add This Widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag SlotTag;

public:
	/* Widget ZOrder, Usefully In WorldWidget, It Decide a Widget How To Hierarchical */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay)
	int32 ZOrder = 0;

	/* Widget Scale, Usefully In WorldWidget, It Decide a Widget Scale Size */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay)
	float Scale = 1.f;

	/* Widget Anchor, Usefully In WorldWidget, It Decide a Widget How To Surrounding */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay)
	FVector2D Anchor = FVector2D(.5f, 1.f);

private:
	uint8 bHasInitialized : 1;
	TWeakObjectPtr<class UScaleBox> ScaleBox;

	/* ==================== IStateInterface ==================== */
public:
	/* Widget Is Created, But Not At Screen */
	virtual void NativeOnCreate() override { IStateInterface::NativeOnCreate(); }

	/* Widget Is Adding To Screen */
	virtual void NativeOnActived() override { IStateInterface::NativeOnActived(); }

	/* Widget Is Already Added */
	virtual void NativeOnActivedFinish() override { IStateInterface::NativeOnActivedFinish(); }

	/* Widget Is Pre Remove From Screen */
	virtual void NativeOnInactived() override { IStateInterface::NativeOnInactived(); }

	/* Widget Is Removed From Screen */
	virtual void NativeOnInactivedFinish() override { IStateInterface::NativeOnInactivedFinish(); }

	/* Widget Is Pre Mark As Garbage */
	virtual void NativeOnDestroy() override { IStateInterface::NativeOnDestroy(); }

	UFUNCTION(BlueprintPure)
	virtual bool GetIsActived() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetIsActived(const bool InActived) override;

protected:
	virtual void OnActiveStateChanged() override;

	/* ==================== IWidgetChildrenInterface ==================== */
public:
	virtual UGenericWidget* GetChildByIndex(int32 InIndex) override;
	virtual void AddChild(UGenericWidget* InWidget) override;
	virtual void AddChild(UGenericWidget* InWidget, int32 InIndex) override;
	virtual void RemoveChild(int32 InIndex) override;
	virtual void RemoveChild(UGenericWidget* InWidget) override;
	virtual void ClearChildren() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnChildAdded(UGenericWidget* InWidget, int32 InIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnChildRemoved(UGenericWidget* InWidget, int32 InIndex);

protected:
	UPROPERTY()
	TArray<TWeakObjectPtr<UGenericWidget>> Children;

	/* ==================== IWidgetAnimationInterface ==================== */
public:
	/* Animation While Widget Is Opening */
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	UWidgetAnimation* ActivedAnimation = nullptr;

	/* Animation While Widget Is PreClosed */
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	UWidgetAnimation* InactivedAnimation = nullptr;

public:
	UFUNCTION(BlueprintPure)
	virtual bool HasWidgetAnimation(bool InIsActive) const override;

	UFUNCTION(BlueprintPure)
	virtual bool IsPlayingWidgetAnimation(bool InIsActive) const override;

	UFUNCTION(BlueprintPure)
	virtual float GetWidgetAnimationDuration(bool InIsActive) override;

	UFUNCTION(BlueprintPure)
	virtual UWidgetAnimation* GetActiveAnimation() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetActiveAnimation(UWidgetAnimation* InAnimation) override;

	UFUNCTION(BlueprintPure)
	virtual UWidgetAnimation* GetInactiveAnimation() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetInactiveAnimation(UWidgetAnimation* InAnimation) override;

	UFUNCTION(BlueprintCallable)
	virtual void PlayWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	virtual void PlayWidgetAnimationRollback(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	virtual void PauseWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	virtual void StopWidgetAnimation(bool InIsActive) override;

protected:
	UFUNCTION()
	virtual void OnWidgetActiveAnimationPlayFinish() override;

	UFUNCTION()
	virtual void OnWidgetInactiveAnimationPlayFinish() override;
};
