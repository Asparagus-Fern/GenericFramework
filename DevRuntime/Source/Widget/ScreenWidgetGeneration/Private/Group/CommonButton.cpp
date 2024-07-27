// Fill out your copyright notice in the Description page of Project Settings.


#include "Group/CommonButton.h"

#include "ScreenWidgetManager.h"
#include "Animation/WidgetAnimationEvent.h"
#include "Debug/DebugType.h"
#include "Event/CommonButtonEvent.h"
#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureHandle.h"
#include "Procedure/ProcedureManager.h"

UCommonButton::UCommonButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bSelectable = true;
	bEnableInteraction = true;

	static ConstructorHelpers::FClassFinder<UCommonButtonStyle> StyleClassFinder(TEXT("	/Script/Engine.Blueprint'/DevRuntime/ScreenWidgetGeneration/Style/ButtonStyle/CBS_Transparent.CBS_Transparent_C'"));
	if (StyleClassFinder.Succeeded())
	{
		Style = StyleClassFinder.Class;
	}
}

void UCommonButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(GetRootWidget()))
	{
		GetRootWidget()->SetVisibility(bEnableInteraction ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::HitTestInvisible);
	}
}

void UCommonButton::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCommonButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCommonButton::NativeOnHovered()
{
	Super::NativeOnHovered();
	ResponseButtonEvent(ECommonButtonResponseEvent::OnHovered);
}

void UCommonButton::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	ResponseButtonEvent(ECommonButtonResponseEvent::OnUnHovered);
}

void UCommonButton::NativeOnClicked()
{
	Super::NativeOnClicked();
	ResponseButtonEvent(ECommonButtonResponseEvent::OnClick);
}

void UCommonButton::NativeOnPressed()
{
	Super::NativeOnPressed();
	ResponseButtonEvent(ECommonButtonResponseEvent::OnPressed);
}

void UCommonButton::NativeOnReleased()
{
	Super::NativeOnReleased();
	ResponseButtonEvent(ECommonButtonResponseEvent::OnReleased);
}

void UCommonButton::NativeOnSelected(bool bBroadcast)
{
	Super::NativeOnSelected(bBroadcast);
	ResponseButtonEvent(ECommonButtonResponseEvent::OnSelected);
}

void UCommonButton::NativeOnDeselected(bool bBroadcast)
{
	Super::NativeOnDeselected(bBroadcast);
	ResponseButtonEvent(ECommonButtonResponseEvent::OnDeselected);
}

void UCommonButton::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);

	Execute_PlayAnimationEvent(this, true);
}

void UCommonButton::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);

	Execute_PlayAnimationEvent(this, false);
}

void UCommonButton::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	IProcedureBaseInterface::Execute_OnCreate(this);
}

void UCommonButton::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	IProcedureBaseInterface::Execute_OnRefresh(this);
}

void UCommonButton::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	IProcedureBaseInterface::Execute_OnDestroy(this);
}

void UCommonButton::SetEnableInteraction(bool InEnableInteraction)
{
	bEnableInteraction = InEnableInteraction;
	if (IsValid(GetRootWidget()))
	{
		GetRootWidget()->SetVisibility(bEnableInteraction ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::HitTestInvisible);
	}
}

void UCommonButton::ResponseButtonEvent(ECommonButtonResponseEvent InResponseEvent, const FSimpleMulticastDelegate& OnFinish)
{
	if (Events.IsEmpty())
	{
		OnFinish.Broadcast();
		return;
	}

	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles = GetResponseModifyEventHandles(InResponseEvent);;
	if (ProcedureInterfaceHandles.IsEmpty())
	{
		ProcedureInterfaceHandles = GetResponseEventHandles(InResponseEvent);
	}

	if (!ProcedureInterfaceHandles.IsEmpty())
	{
		if (IsValid(ActiveProcedureHandle))
		{
			ActiveProcedureHandle->Reset();
		}

		ActiveProcedureHandle = GetManager<UProcedureManager>()->RegisterProcedureHandle(ProcedureInterfaceHandles, OnFinish);
		return;
	}

	OnFinish.Broadcast();
}

TArray<FProcedureInterfaceHandle> UCommonButton::GetResponseEventHandles(ECommonButtonResponseEvent InResponseEvent)
{
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;

	for (const auto& ResponseEvent : GetResponseEvents(InResponseEvent))
	{
		ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(ResponseEvent, ResponseEvent->Response.FindRef(InResponseEvent)));
	}

	return ProcedureInterfaceHandles;
}

TArray<FProcedureInterfaceHandle> UCommonButton::GetResponseModifyEventHandles(ECommonButtonResponseEvent InResponseEvent)
{
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;

	for (const auto& ResponseModifyEvent : GetResponseModifyEvents(InResponseEvent))
	{
		ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(ResponseModifyEvent, ResponseModifyEvent->Response.FindRef(InResponseEvent)));
	}

	return ProcedureInterfaceHandles;
}

TArray<UCommonButtonEvent*> UCommonButton::GetResponseEvents(const ECommonButtonResponseEvent InResponseEvent)
{
	TArray<UCommonButtonEvent*> ResponseEvents;

	for (const auto& Event : Events)
	{
		if (Event->Response.Contains(InResponseEvent))
		{
			ResponseEvents.Add(Event);
		}
	}

	return ResponseEvents;
}

TArray<UCommonButtonEvent*> UCommonButton::GetResponseModifyEvents(ECommonButtonResponseEvent InResponseEvent)
{
	TArray<UCommonButtonEvent*> ResponseEvents;
	
	TArray<FCommonButtonEventModify> ModifyEvents = GetSelected() ? ModifyPushEvents : ModifyPopEvents;
	if (!ModifyEvents.IsEmpty())
	{
		for (auto& ModifyEvent : ModifyEvents)
		{
			if (ModifyEvent.CanModify(GetSelected()))
			{
				for (const auto& Event : ModifyEvent.ModifyEvent)
				{
					if (Event->Response.Contains(InResponseEvent))
					{
						ResponseEvents.Add(Event);
					}
				}
			}
		}
	}

	return ResponseEvents;
}

UWidgetAnimationEvent* UCommonButton::GetAnimationEvent_Implementation() const
{
	return AnimationEvent;
}

void UCommonButton::SetAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent)
{
	IWidgetAnimationInterface::SetAnimationEvent_Implementation(InAnimationEvent);
	AnimationEvent = InAnimationEvent;
}

bool UCommonButton::HasAnimationEvent_Implementation() const
{
	return IsValid(AnimationEvent);
}

void UCommonButton::PlayAnimationEvent_Implementation(bool InIsActive)
{
	IWidgetAnimationInterface::PlayAnimationEvent_Implementation(InIsActive);

	if (IsValid(AnimationEvent))
	{
		AnimationEvent->SetTargetWidget(this);

		if (InIsActive)
		{
			AnimationEvent->NativeOnActived();
		}
		else
		{
			AnimationEvent->NativeOnInactived();
		}
	}
}
