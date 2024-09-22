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
}

bool UInteractableUserWidgetBase::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	/* 将自身WidgetTree包裹在CommonButton的WidgetTree下 */
	auto WrapWithCommonButton = [this]()
	{
		UWidgetTree* NewWidgetTree = NewObject<UWidgetTree>(this, TEXT("WidgetTree"), RF_Transient);
		NewWidgetTree->RootWidget = WidgetTree->RootWidget;

		ActiveCommonButton = DuplicateObject(CommonButton, this);
		ActiveCommonButton->WidgetTree = NewWidgetTree;

		WidgetTree->RootWidget = ActiveCommonButton;
	};

	if (bInitializedThisCall)
	{
		ActiveCommonButton = nullptr;

		if (IsValid(CommonButton) && WidgetTree->RootWidget)
		{
			/* 运行时始终包裹 */
			if (IsValid(GetManager<UScreenWidgetManager>()))
			{
				WrapWithCommonButton();
			}
			/* 编辑器下如果勾选bPreview则进行包裹 */
			else if (bPreview)
			{
				WrapWithCommonButton();
			}
		}
	}

	return bInitializedThisCall;
}

void UInteractableUserWidgetBase::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
	Super::OnDesignerChanged(EventArgs);
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
		OnButtonSelectedChanged(true);
		OnSelectedChanged.Broadcast(this, true);
		break;

	case ECommonButtonResponseEvent::OnDeselected:
		OnButtonSelectedChanged(false);
		OnSelectedChanged.Broadcast(this, false);
		break;

	case ECommonButtonResponseEvent::OnClick:
		OnButtonClicked();
		OnClicked.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnHovered:
		OnButtonHovered();
		OnHovered.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnUnHovered:
		OnButtonUnhovered();
		OnUnhovered.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnPressed:
		OnButtonPressed();
		OnPressed.Broadcast(this);
		break;

	case ECommonButtonResponseEvent::OnReleased:
		OnButtonReleased();
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
