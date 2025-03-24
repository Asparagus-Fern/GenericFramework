// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Blueprint/UserWidget.h"
#include "Interface/StateInterface.h"
#include "UserWidgetBase.generated.h"

class UWidgetEntity;
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
	GENERATED_BODY()

	friend UWidgetEntity;

protected:
	UUserWidgetBase(const FObjectInitializer& ObjectInitializer);
	virtual void OnWidgetRebuilt() override;
	virtual bool Initialize() override;
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "DevUserWidget", "User Widget Base"); }
#endif

	/* ==================== UUserWidgetBase ==================== */
public:
	/* Unique Tag To Mark Which Slot To Add This Widget */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag SlotTag;

	/* While This Widget Is Opening, The Temporary HUD Will be Added, To Provide The Slot This Widget Need */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UTemporaryHUD>> TemporaryHUDs;

public:
	/* Widget ZOrder, Usefully In WorldWidgetComponent3D, It Decide a Widget How To Hierarchical */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	int32 ZOrder = 0;

	/* Widget Scale, Usefully In WorldWidgetComponent3D, It Can Make Widget More Clear */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	float Scale = 1.f;

	/* Widget Anchor, Usefully In WorldWidgetComponent3D, It Decide a Widget How To Surrounding you */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	FVector2D Anchor = FVector2D(.5f, 1.f);

protected:
	uint8 bHasInitialized : 1;

private:
	TWeakObjectPtr<class UScaleBox> ScaleBox;

	/* ==================== WidgetEntity ==================== */
public:
	UFUNCTION(BlueprintPure)
	UWidgetEntity* GetWidgetEntity();

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"))
	UWidgetEntity* GetWidgetEntityByClass(TSubclassOf<UWidgetEntity> InClass);

	UFUNCTION(BlueprintCallable)
	void SetWidgetEntity(UWidgetEntity* InWidgetEntity);

public:
	template <typename T>
	T* GetWidgetEntity()
	{
		return Cast<T>(WidgetEntity);
	}

public:
	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<UWidgetEntity> WidgetEntity = nullptr;

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

protected:
	UFUNCTION()
	virtual void OnWidgetActiveAnimationFinish();

	UFUNCTION()
	virtual void OnWidgetInactiveAnimationFinish();

private:
	FWidgetAnimationDynamicEvent WidgetActiveAnimationFinishBinding;
	FWidgetAnimationDynamicEvent WidgetInactiveAnimationFinishBinding;
};
