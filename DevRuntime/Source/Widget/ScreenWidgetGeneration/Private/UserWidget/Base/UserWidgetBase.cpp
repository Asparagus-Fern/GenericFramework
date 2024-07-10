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

UWidgetAnimationEvent* UUserWidgetBase::GetAnimationEvent_Implementation() const
{
	return AnimationEvent;
}

void UUserWidgetBase::SetAnimationEvent_Implementation(UWidgetAnimationEvent* InAnimationEvent)
{
	IWidgetAnimationInterface::SetAnimationEvent_Implementation(InAnimationEvent);
	AnimationEvent = InAnimationEvent;
}

bool UUserWidgetBase::HasAnimationEvent_Implementation() const
{
	return IsValid(AnimationEvent);
}

void UUserWidgetBase::PlayAnimationEvent_Implementation(bool InIsActive)
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

void UUserWidgetBase::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);

	Execute_PlayAnimationEvent(this, true);
}

void UUserWidgetBase::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);

	Execute_PlayAnimationEvent(this, false);
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
