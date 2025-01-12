// Fill out your copyright notice in the Description page of Project Settings.

#include "UWidget/Override/GameplayTagSlot.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_HUD, "UI.HUD");

UGameplayTagSlot::FGameplayTagSlotDelegate UGameplayTagSlot::OnBuildGameplayTagSlot;
UGameplayTagSlot::FGameplayTagSlotDelegate UGameplayTagSlot::OnRemoveGameplayTagSlot;

TSharedRef<SWidget> UGameplayTagSlot::RebuildWidget()
{
	if (IsDesignTime())
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(EVerticalAlignment::VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(SlotTag.GetTagName().ToString()))
			];
	}
	else
	{
		if (SlotTag.IsValid() && !bManualRegistration)
		{
			OnBuildGameplayTagSlot.Broadcast(this);
		}

		return Super::RebuildWidget();
	}
}

void UGameplayTagSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	if (!IsDesignTime())
	{
		if (SlotTag.IsValid())
		{
			OnRemoveGameplayTagSlot.Broadcast(this);
		}
	}
}

void UGameplayTagSlot::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);
	OnSlotContentAdded.Broadcast(GetChildAt(0));
}

void UGameplayTagSlot::OnSlotRemoved(UPanelSlot* InSlot)
{
	OnSlotContentAdded.Broadcast(GetChildAt(0));
	Super::OnSlotRemoved(InSlot);
}
