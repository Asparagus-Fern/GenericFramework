// Fill out your copyright notice in the Description page of Project Settings.


#include "Group/CommonButton.h"

#include "Debug/DebugType.h"
#include "Event/CommonButtonEvent.h"
#include "Procedure/ProcedureHandle.h"

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

	if (IsValid(GetRootWidget()))
	{
		GetRootWidget()->SetVisibility(bEnableInteraction ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::HitTestInvisible);
	}
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

void UCommonButton::NativeOnOpen()
{
	IUserWidgetInterface::NativeOnOpen();
	IUserWidgetInterface::Execute_OnOpen(this);
}

void UCommonButton::NativeOnClose()
{
	IUserWidgetInterface::NativeOnClose();
	IUserWidgetInterface::Execute_OnClose(this);
}

void UCommonButton::NativeOnCreate()
{
	IUserWidgetInterface::NativeOnCreate();
	IUserWidgetInterface::Execute_OnCreate(this);
}

void UCommonButton::NativeOnRefresh()
{
	IUserWidgetInterface::NativeOnRefresh();
	IUserWidgetInterface::Execute_OnRefresh(this);
}

void UCommonButton::NativeOnDestroy()
{
	IUserWidgetInterface::NativeOnDestroy();
	IUserWidgetInterface::Execute_OnDestroy(this);
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

	UProcedureHandle* ProcedureHandle = NewObject<UProcedureHandle>(this);
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;

	for (const auto& Event : Events)
	{
		if (Event->ResponseEvent.Contains(InResponseEvent))
		{
			ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(Event, Event->ResponseEvent.FindRef(InResponseEvent)));
		}
	}

	ProcedureHandle->Handle(ProcedureInterfaceHandles);
}
