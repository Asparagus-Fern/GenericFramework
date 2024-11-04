// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Base/InteractableUserWidgetBase.h"

#include "ScreenWidgetManager.h"
#include "Event/CommonButtonEvent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ButtonSlot.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "Group/CommonButton.h"
#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

UInteractableUserWidgetBase::FBuildInteractableWidgetGroup UInteractableUserWidgetBase::AddInteractableWidget;
UInteractableUserWidgetBase::FBuildInteractableWidgetGroup UInteractableUserWidgetBase::RemoveInteractableWidget;

UInteractableUserWidgetBase::UInteractableUserWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// CommonButton = CreateDefaultSubobject<UCommonButton>("CommonButton");

	ResponseState.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseState.Add(ECommonButtonResponseEvent::OnDeselected, false);

	SetVisibilityInternal(ESlateVisibility::Visible);
}

bool UInteractableUserWidgetBase::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		if (IsValid(CommonButton) && WidgetTree->RootWidget)
		{
			// UOverlay* RootOverlayRaw = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), FName(TEXT("Overlay")));
			// RootOverlay = RootOverlayRaw;
			//
			// {
			// 	ActiveCommonButton = DuplicateObject(CommonButton, this);
			// 	UOverlaySlot* OverlaySlot = RootOverlayRaw->AddChildToOverlay(ActiveCommonButton);
			// 	OverlaySlot->SetPadding(FMargin());
			// 	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			// 	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			// }
			//
			// {
			// 	UOverlaySlot* OverlaySlot = RootOverlayRaw->AddChildToOverlay(WidgetTree->RootWidget);
			// 	OverlaySlot->SetPadding(FMargin());
			// 	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			// 	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			// }
			//
			// WidgetTree->RootWidget = RootOverlayRaw;

			CommonButton->Initialize();

			UWidgetTree* NewWidgetTree = NewObject<UWidgetTree>(this, TEXT("WidgetTree"), RF_Transient);
			NewWidgetTree->RootWidget = WidgetTree->RootWidget;

			ActiveCommonButton = DuplicateObject(CommonButton, this, "ActiveCommonButton");
			ActiveCommonButton->WidgetTree = NewWidgetTree;
			ActiveCommonButton->InitializeForce();

			WidgetTree->RootWidget = ActiveCommonButton;
		}
	}

	return bInitializedThisCall;
}

void UInteractableUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	/* 绑定按钮的所有响应 */
	if (IsValid(ActiveCommonButton))
	{
		ActiveCommonButton->OnButtonResponse.AddUObject(this, &UInteractableUserWidgetBase::HandleButtonResponse);

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

void UInteractableUserWidgetBase::NativeDestruct()
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

void UInteractableUserWidgetBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (ActiveCommonButton)
	{
		ActiveCommonButton->SynchronizeProperties();
	}
}

void UInteractableUserWidgetBase::NativeOnButtonSelectedChanged(bool Selected)
{
	OnButtonSelectedChanged(Selected);
}

void UInteractableUserWidgetBase::NativeOnButtonClicked()
{
	OnButtonClicked();
}

void UInteractableUserWidgetBase::NativeOnButtonDoubleClicked()
{
	OnButtonDoubleClicked();
}

void UInteractableUserWidgetBase::NativeOnButtonHovered()
{
	if (!ActiveCommonButton->GetSelected())
	{
		OnButtonHovered();
	}
}

void UInteractableUserWidgetBase::NativeOnButtonUnhovered()
{
	if (!ActiveCommonButton->GetSelected())
	{
		OnButtonUnhovered();
	}
}

void UInteractableUserWidgetBase::NativeOnButtonPressed()
{
	OnButtonPressed();
}

void UInteractableUserWidgetBase::NativeOnButtonReleased()
{
	OnButtonReleased();
}

TArray<UCommonButtonEvent*> UInteractableUserWidgetBase::GetResponseEvents(const bool TargetEventState)
{
	return TargetEventState ? ActivedEvents : InactivedEvents;
}

void UInteractableUserWidgetBase::HandleButtonResponse(UCommonButton* Button, ECommonButtonResponseEvent InResponseEvent)
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

UProcedureProxy* UInteractableUserWidgetBase::HandleButtonResponseEvent(TArray<UCommonButtonEvent*> TargetEvents, const bool TargetEventState, const FSimpleDelegate OnFinish)
{
	if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>())
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
