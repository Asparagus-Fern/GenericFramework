// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidget/SLineSegment.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SLineSegment::Construct(const FArguments& InArgs)
{
	Thickness = InArgs._Thickness;
	Offset = InArgs._Offset;
	LineColor = InArgs._LineColor;
	LinePoints = InArgs._LinePoint;
	Content = InArgs._Content.Widget;

	ChildSlot
	[
		Content.ToSharedRef()
	];
}

int32 SLineSegment::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const TArray<FVector2D> Points = CalculatePoints();
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points, ESlateDrawEffect::None, LineColor, true, Thickness);
	LayerId++;

	int32 Result = LayerId;;
	if (Content.IsValid() && !Points.IsEmpty())
	{
		const FVector2D LastPoint = Points.Last();
		const FVector2D ContentSize = Content->GetDesiredSize();
		const FVector2D RenderTransiation = LastPoint - FVector2D(ContentSize.X, ContentSize.Y);

		Content->SetRenderTransform(FSlateRenderTransform(RenderTransiation));
	}

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);;
}

TArray<FVector2D> SLineSegment::CalculatePoints() const
{
	TArray<FVector2D> Points;

	FVector2D LastPointPosition = FVector2D::Zero();
	Points.Add(LastPointPosition);

	/* 计算每个点连接上一个点后的位置 */
	for (auto& LinePoint : LinePoints)
	{
		FVector2D PointPositon = CalculatePoint(LinePoint);
		FVector2D ResultPosition = PointPositon + LastPointPosition;
		LastPointPosition = PointPositon;

		Points.Add(ResultPosition);
	}

	return Points;
}

TArray<FVector2D> SLineSegment::CalculatePoints(const float Alpha) const
{
	/* 约束到 0~1 */
	const float ClampAlpha = FMath::Clamp(Alpha, 0.f, 1.f);

	/* 最后计算完返回的点 */
	TArray<FVector2D> TargetPoints;
	TargetPoints.Add(FVector2D::Zero());

	/* 获取所有线段总长度，用Alpha计算出需要的长度 */
	const float Length = GetLineSegmentLength();
	const float TargetLength = FMath::Lerp(0.f, Length, ClampAlpha);

	float CurrentLength = 0.f;
	FVector2D CurrentPointPosition = FVector2D::Zero();

	for (auto& LinePoint : LinePoints)
	{
		/* 所需长度介于当前点和上一个点之间 */
		if (CurrentLength + LinePoint.Length > TargetLength)
		{
			/* 使用当前点的角度和超出上一个点的长度计算最后一个点的位置 */
			CurrentPointPosition += CalculatePoint(FLineSegmentPoint(LinePoint.Angle, TargetLength - CurrentLength));
			TargetPoints.Add(CurrentPointPosition);
			break;
		}
		/* 所需长度已经超出这个点的长度 */
		else
		{
			/* 计算这个点的位置 */
			CurrentPointPosition += CalculatePoint(LinePoint);
			CurrentLength += LinePoint.Length;
			TargetPoints.Add(CurrentPointPosition);
		}
	}

	return TargetPoints;
}

FVector2D SLineSegment::CalculatePoint(const FLineSegmentPoint InLinePoint) const
{
	return FVector2D(InLinePoint.Length * FMath::Cos(UE_DOUBLE_PI / (180.0) * InLinePoint.Angle) + Offset.X, InLinePoint.Length * FMath::Sin(UE_DOUBLE_PI / (180.0) * InLinePoint.Angle) + Offset.Y);
}

float SLineSegment::GetLineSegmentLength() const
{
	float Length = 0.f;

	for (auto& LinePoint : LinePoints)
	{
		Length += LinePoint.Length;
	}

	return Length;
}

void SLineSegment::SetThickness(const float InThickness)
{
	Thickness = InThickness;
}

void SLineSegment::SetOffset(const FVector2D InOffset)
{
	Offset = InOffset;
}

void SLineSegment::SetLineColor(const FLinearColor InLineColor)
{
	LineColor = InLineColor;
}

void SLineSegment::SetLinePoints(const TArray<FLineSegmentPoint>& InLinePoints)
{
	LinePoints = InLinePoints;
}

void SLineSegment::SetContent(const TSharedRef<SWidget>& InContent)
{
	Content = InContent;
	ChildSlot
	[
		Content.ToSharedRef()
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
