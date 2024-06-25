// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidget/SLine.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SLine::Construct(const FArguments& InArgs)
{
	Anchor = InArgs._Anchor;
	Thickness = InArgs._Thickness;
	LinePoints = InArgs._LinePoint;
	Content = InArgs._Content.Widget;

	ChildSlot
	[
		Content.ToSharedRef()
	];
}

int32 SLine::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const TArray<FVector2D> Points = CalculatePoints();
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points, ESlateDrawEffect::None, LineColor, true, Thickness);
	// FSlateDrawElement::MakeDrawSpaceSpline(OutDrawElements,LayerId,)
	LayerId++;

	const int32 Result = SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	if (Content.IsValid() && !Points.IsEmpty())
	{
		const FVector2D LastPoint = Points.Last();
		const FVector2D ContentSize = Content->GetDesiredSize();
		const FVector2D RenderTransiation = LastPoint - FVector2D(ContentSize.X * Anchor.X, ContentSize.Y * Anchor.Y);

		Content->SetRenderTransform(FSlateRenderTransform(RenderTransiation));
	}

	return Result;
}

FVector2D SLine::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	// TArray<FVector2D> Points = CalculatePoints();
	//
	// float MaxPositionX = 0.f;
	// float MinPositionX = 0.f;
	// float MaxPositionY = 0.f;
	// float MinPositionY = 0.f;
	//
	// for (const auto& Point : Points)
	// {
	// 	if (Point.X > MaxPositionX)
	// 	{
	// 		MaxPositionX = Point.X;
	// 	}
	// 	else if (Point.X < MinPositionX)
	// 	{
	// 		MinPositionX = Point.X;
	// 	}
	// 	if (Point.Y > MaxPositionY)
	// 	{
	// 		MaxPositionY = Point.Y;
	// 	}
	// 	else if (Point.Y < MinPositionY)
	// 	{
	// 		MinPositionY = Point.Y;
	// 	}
	// }
	//
	// return FVector2D(MaxPositionX - MinPositionX, MaxPositionY - MinPositionY);

	// if (Content.IsValid())
	// {
	// 	return Content->GetDesiredSize();
	// }

	return SCompoundWidget::ComputeDesiredSize(LayoutScaleMultiplier);

	// return FVector2D::Zero();
}

TArray<FVector2D> SLine::CalculatePoints() const
{
	TArray<FVector2D> Points;

	FVector2D LastPointPosition = FVector2D::Zero();
	Points.Add(LastPointPosition);

	for (auto& LinePoint : LinePoints)
	{
		FVector2D PointPositon = CalculatePoint(LinePoint);
		FVector2D ResultPosition = PointPositon + LastPointPosition;
		LastPointPosition = PointPositon;

		Points.Add(ResultPosition);
	}

	return Points;
}

FVector2D SLine::CalculatePoint(FLinePoint InLinePoint) const
{
	return FVector2D(InLinePoint.Length * FMath::Cos(UE_DOUBLE_PI / (180.0) * InLinePoint.Angle), InLinePoint.Length * FMath::Sin(UE_DOUBLE_PI / (180.0) * InLinePoint.Angle));
}

void SLine::SetAnchor(FVector2D InAnchor)
{
	Anchor = InAnchor;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetThickness(float InThickness)
{
	Thickness = InThickness;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetLineColor(FLinearColor InLineColor)
{
	LineColor = InLineColor;
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetContent(const TSharedRef<SWidget>& InContent)
{
	Content = InContent;
	ChildSlot
	[
		Content.ToSharedRef()
	];

	Invalidate(EInvalidateWidgetReason::Paint);
}

void SLine::SetLinePoints(const TArray<FLinePoint>& InLinePoints)
{
	LinePoints = InLinePoints;
	Invalidate(EInvalidateWidgetReason::Paint);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
