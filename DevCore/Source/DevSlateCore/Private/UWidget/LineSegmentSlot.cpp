// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/LineSegmentSlot.h"

#include "Components/Widget.h"
#include "SWidget/SLineSegment.h"

void ULineSegmentSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void ULineSegmentSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyLineSegment.Reset();
}

void ULineSegmentSlot::BuildSlot(const TSharedRef<SLineSegment>& InLineSegment)
{
	MyLineSegment = InLineSegment;

	SynchronizeProperties();

	MyLineSegment.Pin()->SetContent(Content ? Content->TakeWidget() : SNullWidget::NullWidget);
}
