// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "ScreenWidgetType.h"
#include "UserWidgetBase.h"
#include "InteractableUserWidgetBase.generated.h"

class UScreenWidgetManager;
class UProcedureProxy;

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UInteractableUserWidgetBase : public UUserWidgetBase
{
	GENERATED_BODY()

	friend UScreenWidgetManager;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonResponse, UProcedureProxy*, ProcedureProxy, bool, ResponseState);

public:
	UInteractableUserWidgetBase(const FObjectInitializer& ObjectInitializer);
	virtual bool Initialize() override;
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString GroupName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UCommonButton* CommonButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> ActivedEvents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> InactivedEvents;

	/* true则为激活，表示在该条件下激活按钮 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECommonButtonResponseEvent, bool> ResponseState;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractableWidgetSelectedStateChanged, UInteractableUserWidgetBase*, InteractableWidget, bool, Selected);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableWidgetDelegate, UInteractableUserWidgetBase*, InteractableWidget);

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetSelectedStateChanged OnSelectedChanged;

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetDelegate OnClicked;

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetDelegate OnDoubleClicked;

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetDelegate OnHovered;

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetDelegate OnUnhovered;

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetDelegate OnPressed;

	UPROPERTY(BlueprintAssignable)
	FInteractableWidgetDelegate OnReleased;

	UPROPERTY(BlueprintAssignable)
	FOnButtonResponse OnButtonResponse;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonSelectedChanged(bool Selected);

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonDoubleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonHovered();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonUnhovered();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonReleased();

public:
	UFUNCTION(BlueprintPure)
	TArray<UCommonButtonEvent*> GetResponseEvents(bool TargetEventState);

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FBuildInteractableWidgetGroup, UInteractableUserWidgetBase*, FString)
	static FBuildInteractableWidgetGroup AddInteractableWidget;
	static FBuildInteractableWidgetGroup RemoveInteractableWidget;

	DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnResponseStateChanged, UInteractableUserWidgetBase*, bool);
	FOnResponseStateChanged OnResponseStateChanged;

protected:
	virtual void HandleButtonResponse(UCommonButton* Button, ECommonButtonResponseEvent InResponseEvent);
	virtual UProcedureProxy* HandleButtonResponseEvent(TArray<UCommonButtonEvent*> TargetEvents, bool TargetEventState, FSimpleDelegate OnFinish = FSimpleDelegate());
};
