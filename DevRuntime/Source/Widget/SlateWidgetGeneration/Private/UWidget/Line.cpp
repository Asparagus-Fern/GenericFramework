// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/Line.h"

#include "SWidget/SLine.h"
#include "UWidget/LineSlot.h"

TSharedRef<SWidget> ULine::RebuildWidget()
{
	MyLine = SNew(SLine)
		.Thickness(Thickness)
		.Duration(Duration)
		.CurveType(CurveType)
		.Anchor(Anchor)
		.LinePoint(LinePoints)
		.OnTransitionFinish_UObject(this, &ULine::HandleTransitionFinish);

	if (GetChildrenCount() > 0)
	{
		Cast<ULineSlot>(GetContentSlot())->BuildSlot(MyLine.ToSharedRef());
	}

	SetVisibility(ESlateVisibility::HitTestInvisible);
	return MyLine.ToSharedRef();
}

void ULine::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetAnchor(Anchor);
	SetThickness(Thickness);
	SetLineColor(LineColor);
	SetLinePoints(LinePoints);
}

void ULine::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	MyLine.Reset();
}

UClass* ULine::GetSlotClass() const
{
	return ULineSlot::StaticClass();
}

void ULine::OnSlotAdded(UPanelSlot* InSlot)
{
	if (MyLine.IsValid())
	{
		CastChecked<ULineSlot>(InSlot)->BuildSlot(MyLine.ToSharedRef());
	}
}

void ULine::OnSlotRemoved(UPanelSlot* InSlot)
{
	if (MyLine.IsValid())
	{
		MyLine->SetContent(SNullWidget::NullWidget);
	}
}

float ULine::GetThickness() const
{
	return Thickness;
}

void ULine::SetThickness(const float InThickness)
{
	Thickness = InThickness;
	if (MyLine.IsValid())
	{
		MyLine->SetThickness(Thickness);
	}
}

float ULine::GetDuration() const
{
	return Duration;
}

void ULine::SetDuration(const float InDuration)
{
	Duration = InDuration;
	if (MyLine.IsValid())
	{
		MyLine->SetTransition(Duration, CurveType);
	}
}

ETransitionCurve ULine::GetCurveType() const
{
	return CurveType;
}

void ULine::SetCurveType(const ETransitionCurve InCurveType)
{
	CurveType = InCurveType;
	if (MyLine.IsValid())
	{
		MyLine->SetTransition(Duration, CurveType);
	}
}

FVector2D ULine::GetAnchor() const
{
	return Anchor;
}

void ULine::SetAnchor(const FVector2D InAnchor)
{
	Anchor = InAnchor;
	if (MyLine.IsValid())
	{
		MyLine->SetAnchor(Anchor);
	}
}

FLinearColor ULine::GetLineColor() const
{
	return LineColor;
}

void ULine::SetLineColor(const FLinearColor InLineColor)
{
	LineColor = InLineColor;
	if (MyLine.IsValid())
	{
		MyLine->SetLineColor(LineColor);
	}
}

TArray<FLinePoint> ULine::GetLinePoints() const
{
	return LinePoints;
}

void ULine::SetLinePoints(const TArray<FLinePoint> InLinePoints)
{
	LinePoints = InLinePoints;
	if (MyLine.IsValid())
	{
		MyLine->SetLinePoints(LinePoints);
	}
}

void ULine::PlayTransition(const bool bForward)
{
	if (MyLine.IsValid())
	{
		MyLine->PlayTransition(bForward);
	}
}

TArray<FVector2D> ULine::GetPoints() const
{
	if (MyLine.IsValid())
	{
		return MyLine->CalculatePoints();
	}
	return TArray<FVector2D>{};
}

TArray<FVector2D> ULine::GetPointsByAlpha(const float Alpha) const
{
	if (MyLine.IsValid())
	{
		return MyLine->CalculatePoints(Alpha);
	}
	return TArray<FVector2D>{};
}

float ULine::GetLength() const
{
	if (MyLine.IsValid())
	{
		return MyLine->GetLength();
	}
	return -1.f;
}

void ULine::HandleTransitionFinish()
{
	OnTransitionFinish.Broadcast();
}
