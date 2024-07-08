// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ScreenWidgetType.h"
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
class SCREENWIDGETGENERATION_API UCommonButton : public UCommonButtonBase, public IProcedureInterface, public IProcedureBaseInterface
{
	GENERATED_BODY()

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInteraction;

	UPROPERTY(EditAnywhere, Instanced, Getter, Setter, BlueprintGetter="GetEvents", BlueprintSetter="SetEvents")
	TArray<UCommonButtonEvent*> Events;

public:
	UFUNCTION(BlueprintPure)
	TArray<UCommonButtonEvent*> GetEvents() const;

	UFUNCTION(BlueprintCallable)
	void SetEvents(TArray<UCommonButtonEvent*> InEvents);

protected:
	UPROPERTY(Transient)
	UProcedureHandle* ActiveProcedureHandle = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnButtonEventHandleFinish OnButtonEventHandleFinish;

public:
	void ResponseButtonEvent(ECommonButtonResponseEvent InResponseEvent, const FSimpleMulticastDelegate& OnFinish = FSimpleMulticastDelegate());

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
};
