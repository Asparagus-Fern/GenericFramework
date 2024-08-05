// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/LineSegment.h"

#include "SWidget/SLineSegment.h"
#include "UWidget/LineSegmentSlot.h"

TSharedRef<SWidget> ULineSegment::RebuildWidget()
{
	MyLineSegment = SNew(SLineSegment)
		.Thickness(Thickness)
		.Offset(Offset)
		.LineColor(LineColor)
		.LinePoint(LinePoints);

	if (GetChildrenCount() > 0)
	{
		Cast<ULineSegmentSlot>(GetContentSlot())->BuildSlot(MyLineSegment.ToSharedRef());
	}

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	return MyLineSegment.ToSharedRef();
}

void ULineSegment::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetThickness(Thickness);
	SetOffset(Offset);
	SetLineColor(LineColor);
	SetLinePoints(LinePoints);
}

void ULineSegment::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyLineSegment.Reset();
}

UClass* ULineSegment::GetSlotClass() const
{
	return ULineSegmentSlot::StaticClass();
}

void ULineSegment::OnSlotAdded(UPanelSlot* InSlot)
{
	if (MyLineSegment.IsValid())
	{
		CastChecked<ULineSegmentSlot>(InSlot)->BuildSlot(MyLineSegment.ToSharedRef());
	}
}

void ULineSegment::OnSlotRemoved(UPanelSlot* InSlot)
{
	if (MyLineSegment.IsValid())
	{
		MyLineSegment->SetContent(SNullWidget::NullWidget);
	}
}

float ULineSegment::GetThickness() const
{
	return Thickness;
}

void ULineSegment::SetThickness(const float InThickness)
{
	Thickness = InThickness;
	if (MyLineSegment.IsValid())
	{
		MyLineSegment->SetThickness(Thickness);
	}
}

FVector2D ULineSegment::GetOffset() const
{
	return Offset;
}

void ULineSegment::SetOffset(FVector2D InOffset)
{
	Offset = InOffset;
	if (MyLineSegment.IsValid())
	{
		MyLineSegment->SetOffset(Offset);
	}
}

FLinearColor ULineSegment::GetLineColor() const
{
	return LineColor;
}

void ULineSegment::SetLineColor(const FLinearColor InLineColor)
{
	LineColor = InLineColor;
	if (MyLineSegment.IsValid())
	{
		MyLineSegment->SetLineColor(LineColor);
	}
}

TArray<FLineSegmentPoint> ULineSegment::GetLinePoints() const
{
	return LinePoints;
}

void ULineSegment::SetLinePoints(const TArray<FLineSegmentPoint> InLinePoints)
{
	LinePoints = InLinePoints;
	if (MyLineSegment.IsValid())
	{
		MyLineSegment->SetLinePoints(LinePoints);
	}
}


TArray<FVector2D> ULineSegment::GetPoints() const
{
	if (MyLineSegment.IsValid())
	{
		return MyLineSegment->CalculatePoints();
	}
	return TArray<FVector2D>{};
}

TArray<FVector2D> ULineSegment::GetPointsByAlpha(const float Alpha) const
{
	if (MyLineSegment.IsValid())
	{
		return MyLineSegment->CalculatePoints(Alpha);
	}
	return TArray<FVector2D>{};
}

float ULineSegment::GetLength() const
{
	if (MyLineSegment.IsValid())
	{
		return MyLineSegment->GetLineSegmentLength();
	}
	return -1.f;
}
