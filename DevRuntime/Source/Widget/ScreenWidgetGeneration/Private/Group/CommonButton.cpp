// Fill out your copyright notice in the Description page of Project Settings.


#include "Group/CommonButton.h"

#include "ScreenWidgetManager.h"
#include "Animation/WidgetAnimationEvent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/NamedSlot.h"
#include "Components/SizeBox.h"
#include "Event/CommonButtonEvent.h"

UCommonButton::UCommonButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bSelectable = true;
	bApplyAlphaOnDisable = false;

	static ConstructorHelpers::FClassFinder<UCommonButtonStyle> StyleClassFinder(TEXT("/Script/Engine.Blueprint'/DevRuntime/ScreenWidgetGeneration/ButtonStyle/CBS_Transparent.CBS_Transparent_C'"));
	if (StyleClassFinder.Succeeded())
	{
		Style = StyleClassFinder.Class;
	}

	SetVisibilityInternal(ESlateVisibility::Visible);
}

TSharedRef<SWidget> UCommonButton::RebuildWidget()
{
	return Super::RebuildWidget();
}

bool UCommonButton::Initialize()
{
	// return Super::Initialize();
	return true;
}

bool UCommonButton::InitializeForce()
{
	return UCommonButtonBase::Initialize();
}

void UCommonButton::NativePreConstruct()
{
	Super::NativePreConstruct();
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
	HandleResponse(ECommonButtonResponseEvent::OnHovered);
}

void UCommonButton::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	HandleResponse(ECommonButtonResponseEvent::OnUnHovered);
}

void UCommonButton::NativeOnClicked()
{
	Super::NativeOnClicked();
	HandleResponse(ECommonButtonResponseEvent::OnClick);
}

void UCommonButton::NativeOnPressed()
{
	Super::NativeOnPressed();
	HandleResponse(ECommonButtonResponseEvent::OnPressed);
}

void UCommonButton::NativeOnReleased()
{
	Super::NativeOnReleased();
	HandleResponse(ECommonButtonResponseEvent::OnReleased);
}

void UCommonButton::NativeOnSelected(bool bBroadcast)
{
	Super::NativeOnSelected(bBroadcast);
	HandleResponse(ECommonButtonResponseEvent::OnSelected);
	DPRINT(Log, TEXT("1"))
}

void UCommonButton::NativeOnDeselected(bool bBroadcast)
{
	Super::NativeOnDeselected(bBroadcast);
	HandleResponse(ECommonButtonResponseEvent::OnDeselected);
	DPRINT(Log, TEXT("2"))
}

void UCommonButton::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);
}

void UCommonButton::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);
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

void UCommonButton::HandleResponse(ECommonButtonResponseEvent InResponseEvent)
{
	OnButtonResponse.Broadcast(this, InResponseEvent);
}
