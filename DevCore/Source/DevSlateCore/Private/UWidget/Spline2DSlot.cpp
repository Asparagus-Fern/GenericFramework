// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/Spline2DSlot.h"

#include "Components/Widget.h"
#include "SWidget/SSpline2D.h"

void USpline2DSlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetHorizontalAlignment(HorizontalAlignment);
	SetVerticalAlignment(VerticalAlignment);
	SetOffset(Offset);
	SetValue(Value);
}

void USpline2DSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	Slot = nullptr;
	MySpline2D.Reset();
}

void USpline2DSlot::BuildSlot(TSharedRef<SSpline2D> InUMGSpline)
{
	MySpline2D = InUMGSpline;

	InUMGSpline->AddSlot()
		.Expose(Slot)
		.Value(Value)
		.HAlign(HorizontalAlignment)
		.VAlign(VerticalAlignment)
		[
			Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()
		];

	SynchronizeProperties();
}

EHorizontalAlignment USpline2DSlot::GetHorizontalAlignment() const
{
	return HorizontalAlignment;
}

void USpline2DSlot::SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if (Slot)
	{
		Slot->SetHorizontalAlignment(InHorizontalAlignment);
	}
}

EVerticalAlignment USpline2DSlot::GetVerticalAlignment() const
{
	return VerticalAlignment;
}

void USpline2DSlot::SetVerticalAlignment(EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if (Slot)
	{
		Slot->SetVerticalAlignment(InVerticalAlignment);
	}
}

FVector2D USpline2DSlot::GetOffset() const
{
	return Offset;
}

void USpline2DSlot::SetOffset(FVector2D InOffset)
{
	Offset = InOffset;
	if (Slot)
	{
		Slot->SetOffset(InOffset);
	}
}

float USpline2DSlot::GetValue() const
{
	return Value;
}

void USpline2DSlot::SetValue(float InValue)
{
	Value = InValue;
	if (Slot)
	{
		Slot->SetValue(InValue);
	}
}
