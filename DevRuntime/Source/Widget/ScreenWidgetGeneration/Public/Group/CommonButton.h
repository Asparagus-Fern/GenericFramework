// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ScreenWidgetType.h"
#include "Animation/WidgetAnimationInterface.h"
#include "Procedure/ProcedureBaseInterface.h"
#include "Procedure/ProcedureInterface.h"
#include "CommonButton.generated.h"

class UWidgetAnimationEvent;
class UProcedureHandle;
class UCommonButtonEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonEventHandleFinish);

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCommonButton : public UCommonButtonBase
                                                 , public IProcedureInterface
                                                 , public IProcedureBaseInterface
                                                 , public IWidgetAnimationInterface
{
	GENERATED_BODY()

	friend UCommonButtonGroup;

	/* UCommonButtonBase */
public:
	UCommonButton(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	virtual void NativeOnClicked() override;
	virtual void NativeOnPressed() override;
	virtual void NativeOnReleased() override;
	virtual void NativeOnSelected(bool bBroadcast) override;
	virtual void NativeOnDeselected(bool bBroadcast) override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnRefresh() override;
	virtual void NativeOnDestroy() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bEnableInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UCommonButtonEvent*> Events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCommonButtonEventModify> ModifyEvents;

public:
	UFUNCTION(BlueprintCallable)
	void SetEnableInteraction(bool InEnableInteraction);

protected:
	UPROPERTY(Transient)
	UProcedureHandle* ActiveProcedureHandle = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnButtonEventHandleFinish OnButtonEventHandleFinish;

public:
	void ResponseButtonEvent(ECommonButtonResponseEvent InResponseEvent, const FSimpleMulticastDelegate& OnFinish = FSimpleMulticastDelegate());

	/* IWidgetAnimationInterface */
public:
	virtual UWidgetAnimationEvent* GetAnimationEvent_Implementation() const override;
	virtual void SetAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent) override;
	virtual bool HasAnimationEvent_Implementation() const override;
	virtual void PlayAnimationEvent_Implementation(bool InIsActive) override;

public:
	UPROPERTY(EditAnywhere, Instanced)
	UWidgetAnimationEvent* AnimationEvent = nullptr;
};
