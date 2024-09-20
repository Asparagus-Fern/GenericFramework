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
                                                   , public IProcedureBaseInterface
{
	GENERATED_UCLASS_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "DevUserWidget", "User Widget Base"); }
#endif
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

	/* IWidgetAnimationInterface */
public:
	virtual bool HasAnimationEvent_Implementation(bool InIsActive) const override;
	virtual UWidgetAnimationEvent* GetActiveAnimationEvent_Implementation() const override;
	virtual void SetActiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual UWidgetAnimationEvent* GetInactiveAnimationEvent_Implementation() const override;
	virtual void SetInactiveAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual void PlayAnimationEvent_Implementation(bool InIsActive) override;
	virtual float GetAnimationDuration_Implementation(bool InIsActive) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI"))
	FGameplayTag SelfTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag SlotTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UTemporaryHUD>> TemporaryHUDs;

	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* ActiveAnimationEvent = nullptr;

	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* InactiveAnimationEvent = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	FVector2D Anchor = FVector2D(.5f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	int32 ZOrder = 0;

	UPROPERTY(VisibleAnywhere)
	bool bIsActived = false;

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetAnchorOffset() const;

	UFUNCTION(BlueprintPure)
	bool GetIsActived() const;

	UFUNCTION(BlueprintCallable)
	void SetIsActived(const bool InActived);
};
