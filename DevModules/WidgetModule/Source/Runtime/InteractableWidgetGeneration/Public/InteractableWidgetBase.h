// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "InteractableWidgetBase.generated.h"

class UScreenWidgetManager;
class UProcedureProxy;

/**
 * 
 */
UCLASS(Abstract)
class INTERACTABLEWIDGETGENERATION_API UInteractableWidgetBase : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonResponse, UProcedureProxy*, ProcedureProxy, bool, ResponseState);

public:
	UInteractableWidgetBase(const FObjectInitializer& ObjectInitializer);
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/* UInteractableUserWidgetBase */
public:
	/* 不为空时，会创建按钮组，所有相同组名的Widget，会被加入到该按钮组 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString GroupName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonPressMethod::Type> PressMethod;

private:
	TWeakObjectPtr<class UButton> RootButton;


	/* !!!!!! */
public:
	// /* 按钮响应设置，只作参数的配置，todo:考虑弃用CommonButton，封装成按钮逻辑基类 */
	// UPROPERTY(EditAnywhere, Instanced)
	// UCommonButton* CommonButton = nullptr;
	//
	// /* 激活的按钮，将从CommonButton复制，因为更改WidgetTree导致细节面板无法编辑的原因，CommonButton只作参数配置，ActiveCommonButton为实际展示的按钮 */
	// UPROPERTY(BlueprintReadOnly, Transient)
	// UCommonButton* ActiveCommonButton = nullptr;
	//
	// /* 由未激活到激活的按钮事件 */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	// TArray<UCommonButtonEvent*> ActivedEvents;
	//
	// /* 由激活到未激活的按钮事件 */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	// TArray<UCommonButtonEvent*> InactivedEvents;
	//
	// /* true则为激活，表示在该条件下激活按钮 */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TMap<ECommonButtonResponseEvent, bool> ResponseState;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractableWidgetSelectedStateChanged, UInteractableWidgetBase*, InteractableWidget, bool, Selected);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableWidgetDelegate, UInteractableWidgetBase*, InteractableWidget);

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
	virtual void NativeOnButtonSelectedChanged(bool Selected);

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonClicked();
	virtual void NativeOnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonDoubleClicked();
	virtual void NativeOnButtonDoubleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonHovered();
	virtual void NativeOnButtonHovered();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonUnhovered();
	virtual void NativeOnButtonUnhovered();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonPressed();
	virtual void NativeOnButtonPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonReleased();
	virtual void NativeOnButtonReleased();

	// public:
	// 	UFUNCTION(BlueprintPure)
	// 	TArray<UCommonButtonEvent*> GetResponseEvents(bool TargetEventState);

	// public:
	// 	DECLARE_MULTICAST_DELEGATE_TwoParams(FBuildInteractableWidgetGroup, UInteractableWidgetBase*, FString)
	// 	static FBuildInteractableWidgetGroup AddInteractableWidget;
	// 	static FBuildInteractableWidgetGroup RemoveInteractableWidget;
	//
	// 	DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnResponseStateChanged, UInteractableWidgetBase*, bool);
	// 	FOnResponseStateChanged OnResponseStateChanged;

	// protected:
	// 	TWeakObjectPtr<class UOverlay> RootOverlay;

	// protected:
	// 	virtual void HandleButtonResponse(UCommonButton* Button, ECommonButtonResponseEvent InResponseEvent);
	// 	virtual UProcedureProxy* HandleButtonResponseEvent(TArray<UCommonButtonEvent*> TargetEvents, bool TargetEventState, FSimpleDelegate OnFinish = FSimpleDelegate());
};
