// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableWidgetBase.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Manager/ManagerProxy.h"
#include "Procedure/ProcedureManager.h"

UInteractableWidgetBase::UInteractableWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ResponseState.Add(ECommonButtonResponseEvent::OnSelected, true);
	// ResponseState.Add(ECommonButtonResponseEvent::OnDeselected, false);
	//
	// SetVisibilityInternal(ESlateVisibility::Visible);
}

bool UInteractableWidgetBase::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		UButton* RootButtonRaw = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), FName(TEXT("InteractableWidgetButton")));

		RootButtonRaw->SetClickMethod(ClickMethod);
		RootButtonRaw->SetTouchMethod(TouchMethod);
		RootButtonRaw->SetPressMethod(PressMethod);
		RootButton = RootButtonRaw;

		if (WidgetTree->RootWidget)
		{
			UButtonSlot* NewSlot = Cast<UButtonSlot>(RootButtonRaw->AddChild(WidgetTree->RootWidget));
			NewSlot->SetPadding(FMargin());
			NewSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			NewSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			WidgetTree->RootWidget = RootButtonRaw;

			RootButton->OnClicked.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonClicked);
			RootButton->HandleDoubleClicked.BindUObject(this, &UInteractableWidgetBase::HandleButtonDoubleClicked);
			RootButton->OnReceivedFocus.BindUObject(this, &UInteractableWidgetBase::HandleFocusReceived);
			RootButton->OnLostFocus.BindUObject(this, &UInteractableWidgetBase::HandleFocusLost);
			RootButton->OnPressed.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonPressed);
			RootButton->OnReleased.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonReleased);
		}
	}

	return bInitializedThisCall;
}

void UInteractableWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	/* 绑定按钮的所有响应 */
	if (IsValid(ActiveCommonButton))
	{
		ActiveCommonButton->OnButtonResponse.AddUObject(this, &UInteractableWidgetBase::HandleButtonResponse);

		/* 当GroupName不为空时，请求创建或添加到按钮组 */
		if (!GroupName.IsEmpty())
		{
			AddInteractableWidget.Broadcast(this, GroupName);
		}
	}

	/* 同步到按钮事件 */
	{
		for (const auto& ActivedEvent : ActivedEvents)
		{
			if (IsValid(ActivedEvent))
			{
				ActivedEvent->NativeOnCreate();
			}
		}

		for (const auto& ActivedEvent : InactivedEvents)
		{
			if (IsValid(ActivedEvent))
			{
				ActivedEvent->NativeOnCreate();
			}
		}
	}
}

void UInteractableWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(ActiveCommonButton))
	{
		if (!GroupName.IsEmpty())
		{
			RemoveInteractableWidget.Broadcast(this, GroupName);
		}

		ActiveCommonButton->OnButtonResponse.RemoveAll(this);
	}

	/* 同步到按钮事件 */
	{
		for (const auto& ActivedEvent : ActivedEvents)
		{
			if (IsValid(ActivedEvent))
			{
				ActivedEvent->NativeOnDestroy();
			}
		}

		for (const auto& ActivedEvent : InactivedEvents)
		{
			if (IsValid(ActivedEvent))
			{
				ActivedEvent->NativeOnDestroy();
			}
		}
	}
}

void UInteractableWidgetBase::NativeOnButtonSelectedChanged(bool Selected)
{
	OnButtonSelectedChanged(Selected);
}

void UInteractableWidgetBase::NativeOnButtonClicked()
{
	OnButtonClicked();
}

void UInteractableWidgetBase::NativeOnButtonDoubleClicked()
{
	OnButtonDoubleClicked();
}

void UInteractableWidgetBase::NativeOnButtonHovered()
{
	if (!ActiveCommonButton->GetSelected())
	{
		OnButtonHovered();
	}
}

void UInteractableWidgetBase::NativeOnButtonUnhovered()
{
	if (!ActiveCommonButton->GetSelected())
	{
		OnButtonUnhovered();
	}
}

void UInteractableWidgetBase::NativeOnButtonPressed()
{
	OnButtonPressed();
}

void UInteractableWidgetBase::NativeOnButtonReleased()
{
	OnButtonReleased();
}

TArray<UCommonButtonEvent*> UInteractableWidgetBase::GetResponseEvents(const bool TargetEventState)
{
	return TargetEventState ? ActivedEvents : InactivedEvents;
}

void UInteractableWidgetBase::HandleButtonResponse(UCommonButton* Button, ECommonButtonResponseEvent InResponseEvent)
{
	switch (InResponseEvent)
	{
	case ECommonButtonResponseEvent::None:
		break;

	case ECommonButtonResponseEvent::OnSelected:
		NativeOnButtonSelectedChanged(true);
		OnSelectedChanged.Broadcast(this, true);
		break;

	case ECommonButtonResponseEvent::OnDeselected:
		NativeOnButtonSelectedChanged(false);
		OnSelectedChanged.Broadcast(this, false);
		break;

	case ECommonButtonResponseEvent::OnClick:
		NativeOnButtonClicked();
		OnClicked.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnHovered:
		NativeOnButtonHovered();
		OnHovered.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnUnHovered:
		NativeOnButtonUnhovered();
		OnUnhovered.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnPressed:
		NativeOnButtonPressed();
		OnPressed.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnReleased:
		NativeOnButtonReleased();
		OnReleased.Broadcast(this);
		break;
	}

	/* 处理响应事件 */
	if (ResponseState.Contains(InResponseEvent))
	{
		const bool TargetEventState = ResponseState.FindRef(InResponseEvent);
		const TArray<UCommonButtonEvent*> TargetEvents = GetResponseEvents(TargetEventState);

		FReply Handle = FReply::Unhandled();
		if (OnResponseStateChanged.IsBound())
		{
			Handle = OnResponseStateChanged.Execute(this, TargetEventState);
		}

		if (!Handle.IsEventHandled())
		{
			HandleButtonResponseEvent(TargetEvents, TargetEventState);
		}
	}
}

UProcedureProxy* UInteractableWidgetBase::HandleButtonResponseEvent(TArray<UCommonButtonEvent*> TargetEvents, const bool TargetEventState, const FSimpleDelegate OnFinish)
{
	if (UProcedureManager* ProcedureManager = UManagerProxy::Get()->GetManager<UProcedureManager>())
	{
		TArray<UProcedureObject*> ProcedureObjects;
		for (const auto& TargetEvent : TargetEvents)
		{
			if (!IsValid(TargetEvent))
			{
				continue;
			}

			if (TargetEvent->CanExecuteButtonEvent())
			{
				ProcedureObjects.Add(TargetEvent);
			}
		}

		if (!ProcedureObjects.IsEmpty())
		{
			UProcedureProxy* EventProcedureProxy = ProcedureManager->RegisterProcedureHandle(ProcedureObjects, true, OnFinish);
			OnButtonResponse.Broadcast(EventProcedureProxy, TargetEventState);
			return EventProcedureProxy;
		}
	}

	return nullptr;
}
