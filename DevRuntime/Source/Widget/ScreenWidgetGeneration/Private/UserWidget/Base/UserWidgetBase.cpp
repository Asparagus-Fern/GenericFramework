// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Base/UserWidgetBase.h"

#include "Animation/WidgetAnimationEvent.h"

UUserWidgetBase::UUserWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ConstructorHelpers::FClassFinder<UWidgetAnimationEvent> WidgetAnimationEventClass(TEXT("/Script/Engine.Blueprint'/DevRuntime/ScreenWidgetGeneration/AnimationEvent/WAE_Fade.WAE_Fade_C'"));
	// if (WidgetAnimationEventClass.Succeeded())
	// {
	// 	AnimationEvent = static_cast<UWidgetAnimationEvent*>(CreateDefaultSubobject("Widget Animation Event", WidgetAnimationEventClass.Class, WidgetAnimationEventClass.Class, true, false));
	// }
}

TSharedRef<SWidget> UUserWidgetBase::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UUserWidgetBase::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
}

void UUserWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	NativeOnOpen();
}

void UUserWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
}

FGameplayTag UUserWidgetBase::GetSelfTag() const
{
	return SelfTag;
}

FGameplayTag UUserWidgetBase::GetSlotTag() const
{
	return SlotTag;
}

UWidgetAnimationEvent* UUserWidgetBase::GetAnimationEvent() const
{
	return AnimationEvent;
}

void UUserWidgetBase::SetAnimationEvent(UWidgetAnimationEvent* InAnimationEvent)
{
	AnimationEvent = InAnimationEvent;
}

bool UUserWidgetBase::HasAnimationEvent() const
{
	return IsValid(AnimationEvent);
}

void UUserWidgetBase::NativeOnOpen()
{
	IUserWidgetInterface::NativeOnOpen();
	if (IsValid(AnimationEvent)) { AnimationEvent->NativeOnOpen(this); }
	Execute_OnOpen(this);
}

void UUserWidgetBase::NativeOnClose()
{
	IUserWidgetInterface::NativeOnClose();
	if (IsValid(AnimationEvent)) { AnimationEvent->NativeOnClose(this); }
	Execute_OnClose(this);
}

void UUserWidgetBase::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	Execute_OnCreate(this);
}

void UUserWidgetBase::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	Execute_OnDestroy(this);
}

void UUserWidgetBase::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	Execute_OnRefresh(this);
}
