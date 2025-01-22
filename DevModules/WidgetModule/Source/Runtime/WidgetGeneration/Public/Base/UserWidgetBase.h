// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Debug/DebugType.h"
#include "GameplayTagContainer.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Blueprint/UserWidget.h"
#include "Input/UIActionBindingHandle.h"
#include "Interface/StateInterface.h"
#include "UserWidgetBase.generated.h"

class UCommonUISubsystemBase;
class UCommonInputSubsystem;
class UTemporaryHUD;
class UGameHUD;
class UCommonButton;
class UWidgetAnimationEvent;

/**
 * 
 */
UCLASS(Abstract)
class WIDGETGENERATION_API UUserWidgetBase : public UCommonUserWidget, public IWidgetAnimationInterface, public IStateInterface
{
	GENERATED_UCLASS_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "DevUserWidget", "User Widget Base"); }
#endif

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/* ==================== UUserWidgetBase ==================== */
public:
	/* 所在插槽标签 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag SlotTag;

	/* 临时的HUD会在使用时创建，在所有使用到该HUD的Widget都被关闭之后移除 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UTemporaryHUD>> TemporaryHUDs;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	FVector2D Anchor = FVector2D(.5f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	int32 ZOrder = 0;

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetAnchorOffset() const;

	/* ==================== IStateInterface ==================== */
public:
	/* 表示Widget已经创建，但未添加到屏幕 */
	virtual void NativeOnCreate() override { IStateInterface::NativeOnCreate(); }

	/* 表示Widget已添加到屏幕 */
	virtual void NativeOnActived() override { IStateInterface::NativeOnActived(); }

	/* 表示Widget已显示 */
	virtual void NativeOnActivedFinish() override { IStateInterface::NativeOnActivedFinish(); }

	/* 表示Widget即将从屏幕移除 */
	virtual void NativeOnInactived() override { IStateInterface::NativeOnInactived(); }

	/* 表示Widget已经从屏幕移除 */
	virtual void NativeOnInactivedFinish() override { IStateInterface::NativeOnInactivedFinish(); }

	/* 表示Widget即将被垃圾回收 */
	virtual void NativeOnDestroy() override { IStateInterface::NativeOnDestroy(); }

	UFUNCTION(BlueprintPure)
	virtual bool GetIsActived() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetIsActived(const bool InActived) override;

	/* ==================== IWidgetAnimationInterface ==================== */
public:
	/* 创建时的动画 */
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	UWidgetAnimation* ActivedAnimation = nullptr;

	/* 移除时的动画 */
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	UWidgetAnimation* InactivedAnimation = nullptr;

public:
	UFUNCTION(BlueprintPure)
	virtual bool HasWidgetAnimation(bool InIsActive) const override;

	UFUNCTION(BlueprintPure)
	virtual bool IsPlayingWidgetAnimation(bool InIsActive) const override;
	
	UFUNCTION(BlueprintPure)
	virtual UWidgetAnimation* GetActiveAnimation() const override;

	UFUNCTION(BlueprintPure)
	virtual UWidgetAnimation* GetInactiveAnimation() const override;

	UFUNCTION(BlueprintCallable)
	virtual void PlayWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	virtual void PlayWidgetAnimationRollback(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	virtual void PauseWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintCallable)
	virtual void StopWidgetAnimation(bool InIsActive) override;

	UFUNCTION(BlueprintPure)
	virtual float GetWidgetAnimationDuration(bool InIsActive) override;

	virtual void SetActiveAnimation_Implementation(UWidgetAnimation* InAnimation) override;
	virtual void SetInactiveAnimation_Implementation(UWidgetAnimation* InAnimation) override;
};
