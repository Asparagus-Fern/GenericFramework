// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/GameplayTagSlot.h"

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
		if (SlotTag.IsValid())
		{
			OnGameplayTagSlotBuild.Broadcast(this);
		}

		return Super::RebuildWidget();
	}
}

void UGameplayTagSlot::BeginDestroy()
{
	if (SlotTag.IsValid())
	{
		OnGameplayTagSlotDestroy.Broadcast(this);
	}

	Super::BeginDestroy();
}
