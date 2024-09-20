// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ScreenWidgetType.h"
#include "Procedure/ProcedureInterface.h"
#include "CommonButton.generated.h"

class UScreenWidgetManager;
class UInteractableUserWidgetBase;
class UCommonButtonEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonEventHandleFinish);

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCommonButton : public UCommonButtonBase
                                                 , public IProcedureInterface
{
	GENERATED_BODY()

	friend UCommonButtonGroup;
	friend UInteractableUserWidgetBase;
	friend UScreenWidgetManager;

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnButtonResponse, UCommonButton*, ECommonButtonResponseEvent)

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

protected:
	FOnButtonResponse OnButtonResponse;
	void HandleResponse(ECommonButtonResponseEvent InResponseEvent);
};
