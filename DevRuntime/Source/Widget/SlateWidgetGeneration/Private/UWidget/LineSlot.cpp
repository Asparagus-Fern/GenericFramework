// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/LineSlot.h"

#include "Components/Widget.h"
#include "SWidget/SLine.h"

void ULineSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void ULineSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyLine.Reset();
}

void ULineSlot::BuildSlot(TSharedRef<SLine> InLine)
{
	MyLine = InLine;

	SynchronizeProperties();

	MyLine.Pin()->SetContent(Content ? Content->TakeWidget() : SNullWidget::NullWidget);
}
