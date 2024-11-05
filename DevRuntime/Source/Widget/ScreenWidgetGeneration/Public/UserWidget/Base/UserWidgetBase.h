// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "GameplayTagContainer.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Blueprint/UserWidget.h"
#include "Procedure/ProcedureInterface.h"
#include "UserWidgetBase.generated.h"

class UTemporaryHUD;
class UGameHUD;
class UCommonButton;
class UWidgetAnimationEvent;

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UUserWidgetBase : public UUserWidget
                                                   , public IWidgetAnimationInterface
                                                   , public IProcedureInterface
{
	GENERATED_UCLASS_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "DevUserWidget", "User Widget Base"); }
#endif
	virtual void NativeConstruct() override;

	/* IProcedureInterface */
public:
	/* 表示Widget已经创建，但未添加到屏幕 */
	virtual void NativeOnCreate() override { IProcedureInterface::NativeOnCreate(); }

	/* 表示Widget创建完成且在屏幕显示 */
	virtual void NativeOnActived() override { IProcedureInterface::NativeOnActived(); }

	/* 表示Widget即将从屏幕移除 */
	virtual void NativeOnInactived() override { IProcedureInterface::NativeOnInactived(); }

	/* 表示Widget完全从屏幕移除，即将被垃圾回收 */
	virtual void NativeOnDestroy() override { IProcedureInterface::NativeOnDestroy(); }

	/* IWidgetAnimationInterface todo:废弃并更换成 UWidgetAnimation */
public:
	virtual bool HasAnimationEvent_Implementation(bool InIsActive) const override;
	virtual UWidgetAnimationEvent* GetActiveAnimationEvent_Implementation() const override;
	virtual void SetActiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual UWidgetAnimationEvent* GetInactiveAnimationEvent_Implementation() const override;
	virtual void SetInactiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual void PlayAnimationEvent_Implementation(bool InIsActive) override;
	virtual float GetAnimationDuration_Implementation(bool InIsActive) override;

public:
	/* 表示自身标签，用于指定获取Widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI"))
	FGameplayTag SelfTag;

	/* 表示所在插槽标签 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag SlotTag;

	/* 临时的HUD会在使用时创建，在所有使用到该HUD的Widget都被关闭之后移除 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UTemporaryHUD>> TemporaryHUDs;

	/* 创建时的动画 todo:废弃并更换成 UWidgetAnimation */
	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* ActiveAnimationEvent = nullptr;

	/* 移除时的动画 todo:废弃并更换成 UWidgetAnimation */
	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* InactiveAnimationEvent = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	FVector2D Anchor = FVector2D(.5f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	int32 ZOrder = 0;

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetAnchorOffset() const;
};
