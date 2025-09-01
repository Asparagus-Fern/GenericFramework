// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Interface/StateInterface.h"
#include "Interface/WidgetChildrenInterface.h"
#include "Interface/WidgetAnimationInterface.h"
#include "GenericWidget.generated.h"

class UCommonUISubsystemBase;
class UCommonInputSubsystem;
class UGenericGameHUD;
class UCommonButton;
class UWidgetAnimationEvent;

/**
 *  
 */
UCLASS(Abstract, MinimalAPI)
class UGenericWidget : public UUserWidget,
                       public IStateInterface,
                       public IWidgetChildrenInterface,
                       public IWidgetAnimationInterface
{
	GENERATED_BODY()

protected:
	WIDGETGENERATION_API UGenericWidget(const FObjectInitializer& ObjectInitializer);
	WIDGETGENERATION_API virtual void OnWidgetRebuilt() override;
	WIDGETGENERATION_API virtual bool Initialize() override;
	WIDGETGENERATION_API virtual void NativeOnInitialized() override;
	WIDGETGENERATION_API virtual void NativePreConstruct() override;
	WIDGETGENERATION_API virtual void NativeConstruct() override;
	WIDGETGENERATION_API virtual void NativeDestruct() override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "DevUserWidget", "User Widget Base"); }
#endif

	/* ==================== UGenericWidget ==================== */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI"))
	FGameplayTag SelfTag = FGameplayTag::EmptyTag;

	/*
	 * Unique Tag To Mark Which Slot To Add This Widget
	 * If Valid : Will Find The Slot To Add This Widget
	 * If NULL  :
	 *   Check This Widget == UGameHUD, If True Will Add To Viewport
	 *   Check This Widget Outer == UGenericWidget, If True Call Outer Widget AddChild To Add This Widget
	 *   If All Fail : Destroy This Widget
	 */
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
	WIDGETGENERATION_API virtual void NativeOnCreate() override;

	/* Widget Is Adding To Screen */
	WIDGETGENERATION_API virtual void NativeOnActived() override;

	/* Widget Is Already Added */
	WIDGETGENERATION_API virtual void NativeOnActivedFinish() override;

	/* Widget Is Pre Remove From Screen */
	WIDGETGENERATION_API virtual void NativeOnInactived() override;

	/* Widget Is Removed From Screen */
	WIDGETGENERATION_API virtual void NativeOnInactivedFinish() override;

	/* Widget Is Pre Mark As Garbage */
	WIDGETGENERATION_API virtual void NativeOnDestroy() override;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API virtual bool GetIsActived() const override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void SetIsActived(const bool InActived) override;

protected:
	WIDGETGENERATION_API virtual void OnActiveStateChanged() override;

	/* ==================== IWidgetChildrenInterface ==================== */
public:
	WIDGETGENERATION_API virtual UGenericWidget* GetChildByIndex(int32 InIndex) override;
	WIDGETGENERATION_API virtual void AddChild(UGenericWidget* InWidget) override;
	WIDGETGENERATION_API virtual void AddChild(UGenericWidget* InWidget, int32 InIndex) override;
	WIDGETGENERATION_API virtual void RemoveChild(int32 InIndex) override;
	WIDGETGENERATION_API virtual void RemoveChild(UGenericWidget* InWidget) override;
	WIDGETGENERATION_API virtual void ClearChildren() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGENERATION_API void OnChildAdded(UGenericWidget* InWidget, int32 InIndex);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGENERATION_API void OnChildRemoved(UGenericWidget* InWidget, int32 InIndex);

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
	WIDGETGENERATION_API virtual bool HasWidgetAnimation(bool InIsActive) const override;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API virtual bool IsPlayingWidgetAnimation(bool InIsActive) const override;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API virtual float GetWidgetAnimationDuration(bool InIsActive) override;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API virtual UWidgetAnimation* GetActiveAnimation() const override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void SetActiveAnimation(UWidgetAnimation* InAnimation) override;

	UFUNCTION(BlueprintPure)
	WIDGETGENERATION_API virtual UWidgetAnimation* GetInactiveAnimation() const override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void SetInactiveAnimation(UWidgetAnimation* InAnimation) override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void PlayWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void PlayWidgetAnimationRollback(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void PauseWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	WIDGETGENERATION_API virtual void StopWidgetAnimation(bool InIsActive) override;

protected:
	UFUNCTION()
	WIDGETGENERATION_API virtual void OnWidgetActiveAnimationPlayFinish() override;

	UFUNCTION()
	WIDGETGENERATION_API virtual void OnWidgetInactiveAnimationPlayFinish() override;
};
