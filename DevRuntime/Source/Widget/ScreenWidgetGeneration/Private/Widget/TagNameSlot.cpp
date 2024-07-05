// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/TagNameSlot.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UTagNameSlot::UTagNameSlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetClipping(EWidgetClipping::ClipToBounds);
}

TSharedRef<SWidget> UTagNameSlot::RebuildWidget()
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
		GetManager<UScreenWidgetManager>()->RegisterSlot(this);
		return Super::RebuildWidget();
	}
}

void UTagNameSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
}
