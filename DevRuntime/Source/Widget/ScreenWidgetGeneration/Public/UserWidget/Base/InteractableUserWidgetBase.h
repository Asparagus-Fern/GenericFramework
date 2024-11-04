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
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void SynchronizeProperties() override;
	
public:
	/* 勾选可以在编辑器下预览运行时下的样式，它会在编辑器下将WidgetTree包裹在CommonButton的WidgetTree下，代价是无法再查看细节面板做出修改 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPreview = false;

	/* 不为空时，会创建按钮组，所有相同组名的Widget，会被加入到该按钮组 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString GroupName;

	/* 按钮响应设置，只作参数的配置 */
	UPROPERTY(EditAnywhere, Instanced)
	UCommonButton* CommonButton = nullptr;

	/* 激活的按钮，将从CommonButton复制，因为更改WidgetTree导致细节面板无法编辑的原因，CommonButton只作参数配置，ActiveCommonButton为实际展示的按钮 */
	UPROPERTY(BlueprintReadOnly, Transient)
	UCommonButton* ActiveCommonButton = nullptr;

	/* 由未激活到激活的按钮事件 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UCommonButtonEvent*> ActivedEvents;

	/* 由激活到未激活的按钮事件 */
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
	TWeakObjectPtr<class UOverlay> RootOverlay;

protected:
	virtual void HandleButtonResponse(UCommonButton* Button, ECommonButtonResponseEvent InResponseEvent);
	virtual UProcedureProxy* HandleButtonResponseEvent(TArray<UCommonButtonEvent*> TargetEvents, bool TargetEventState, FSimpleDelegate OnFinish = FSimpleDelegate());
};
