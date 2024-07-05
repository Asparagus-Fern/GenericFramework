// Fill out your copyright notice in the Description page of Project Settings.


#include "Group/CommonButton.h"

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
	ResponseButtonEvent(ECommonButtonResponseEvent::OnDeselected);
	Super::NativeOnDeselected(bBroadcast);
}

void UCommonButton::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);

	if (IsValid(AnimationEvent))
	{
		AnimationEvent->SetTargetWidget(this);
		AnimationEvent->NativeOnActived();
	}
}

void UCommonButton::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);

	if (IsValid(AnimationEvent))
	{
		AnimationEvent->SetTargetWidget(this);
		AnimationEvent->NativeOnInactived();
	}
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

TArray<UCommonButtonEvent*> UCommonButton::GetEvents() const
{
	return Events;
}

void UCommonButton::SetEvents(TArray<UCommonButtonEvent*> InEvents)
{
	Events = InEvents;
}

void UCommonButton::ResponseButtonEvent(ECommonButtonResponseEvent InResponseEvent)
{
	if (Events.IsEmpty())
	{
		return;
	}

	bool bNeedProcedureHandle = false;
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;
	for (const auto& Event : Events)
	{
		if (IsValid(Event))
		{
			if (Event->ResponseEvent.Contains(InResponseEvent))
			{
				bNeedProcedureHandle = true;
				ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(Event, Event->ResponseEvent.FindRef(InResponseEvent)));
			}
		}
	}

	if (bNeedProcedureHandle)
	{
		if (IsValid(ActiveProcedureHandle))
		{
			ActiveProcedureHandle->Reset();
		}
		
		ActiveProcedureHandle = GetManager<UProcedureManager>()->RegisterProcedureHandle(ProcedureInterfaceHandles);
	}
}

UWidgetAnimationEvent* UCommonButton::GetAnimationEvent() const
{
	return AnimationEvent;
}

void UCommonButton::SetAnimationEvent(UWidgetAnimationEvent* InAnimationEvent)
{
	AnimationEvent = InAnimationEvent;
}

bool UCommonButton::HasAnimationEvent() const
{
	return IsValid(AnimationEvent);;
}
