// Fill out your copyright notice in the Description page of Project Settings.

#include "SWidget/SUMGSpline.h"

#include "UMGSplineType.h"
#include "Spline/UMGSplineBuilder.h"
#include "Spline/UMGSplineRenderBatch.h"

void SUMGSpline::Construct(const FArguments& InArgs)
{
	// Arguments passed onto the slate widget
	SplineInfo = InArgs._SplineInfo;

	SplineDebugInfo = InArgs._SplineDebugInfo;
}

FVector2D SUMGSpline::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	TArray<FUMGSplinePoint> Points = GetUMGSplineInfo().Points;

	if (Points.IsEmpty())
	{
		return FVector2D::ZeroVector;
	}

	FVector2D Min = Points[0].Location;
	FVector2D Max = Points[0].Location;

	for (const auto& Point : GetUMGSplineInfo().Points)
	{
		if (Point.Location.X < Min.X)
		{
			Min.X = Point.Location.X;
		}

		if (Point.Location.Y < Min.Y)
		{
			Min.Y = Point.Location.Y;
		}

		if (Point.Location.X > Max.X)
		{
			Max.X = Point.Location.X;
		}

		if (Point.Location.Y > Max.Y)
		{
			Max.Y = Point.Location.Y;
		}
	}

	return Max - Min;
}

int32 SUMGSpline::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const ESlateDrawEffect DrawEffects = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	int32 OutLayerId = LayerId;
	if (SplineDebugInfo.Get().bDrawWidgetBoarder)
	{
		OutLayerId++;
		PaintWidgetBoarder(AllottedGeometry, OutDrawElements, OutLayerId, MyCullingRect, DrawEffects);
	}

	OutLayerId++;
	if (SplineInfo.Get().BuildCustomVerts)
	{
		PaintSplineCustomVerts(AllottedGeometry, OutDrawElements, OutLayerId, MyCullingRect, DrawEffects, InWidgetStyle);;
	}
	else
	{
		PaintSplineDefault(AllottedGeometry, OutDrawElements, OutLayerId, MyCullingRect, DrawEffects, InWidgetStyle);
	}

	return OutLayerId;
}

FUMGSplineInfo SUMGSpline::GetUMGSplineInfo() const
{
	return SplineInfo.Get();
}

void SUMGSpline::PaintWidgetBoarder(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects) const
{
	const FLinearColor& BoarderColor = SplineDebugInfo.Get().BoarderColor;

	// Boarder
	{
		TArray<FVector2D> LinePoints;
		LinePoints.Add(FVector2D(1.0f, 1.0f));
		LinePoints.Add(FVector2D(AllottedGeometry.GetLocalSize().X - 1.0f, 1.0f));
		LinePoints.Add(FVector2D(AllottedGeometry.GetLocalSize().X - 1.0f, AllottedGeometry.GetLocalSize().Y - 1.0f));
		LinePoints.Add(FVector2D(1.0f, AllottedGeometry.GetLocalSize().Y - 1.0f));
		LinePoints.Add(FVector2D(1.0f, 1.0f));

		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			LinePoints,
			DrawEffects,
			BoarderColor,
			false
		);
	}
}

void SUMGSpline::PaintSplineDefault(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const
{
	if (GetUMGSplineInfo().GetPointNum() > 1)
	{
		const FColor TintColor = (InWidgetStyle.GetColorAndOpacityTint() * GetUMGSplineInfo().TintColor).ToFColor(true);
		const TArray<FUMGSplinePoint>& Points = GetUMGSplineInfo().GetPoints();

		for (int32 i = 0; i < Points.Num() - 1; ++i)
		{
			FVector2D LocalStart = Points[i].Location;
			FVector2D StartDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points[i].Direction;

			FVector2D LocalEnd = Points[i + 1].Location;
			FVector2D EndDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points[i + 1].Direction;

			if ((LocalStart.X != -FLT_MAX) && (LocalStart.Y != -FLT_MAX) && (LocalEnd.X != -FLT_MAX) && (LocalEnd.Y != -FLT_MAX))
			{
				LayerId++;

				FSlateDrawElement::MakeSpline(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(),
					LocalStart,
					StartDir,
					LocalEnd,
					EndDir,
					GetUMGSplineInfo().Thickness,
					DrawEffects,
					TintColor
				);
			}
		}

		if (GetUMGSplineInfo().bClosedLoop)
		{
			const FVector2D LocalStart = Points.Last().Location;
			const FVector2D StartDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points.Last().Direction;

			const FVector2D LocalEnd = Points[0].Location;
			const FVector2D EndDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points[0].Direction;

			if ((LocalStart.X != -FLT_MAX) && (LocalStart.Y != -FLT_MAX) && (LocalEnd.X != -FLT_MAX) && (LocalEnd.Y != -FLT_MAX))
			{
				LayerId++;

				FSlateDrawElement::MakeSpline(
					OutDrawElements,
					LayerId,
					AllottedGeometry.ToPaintGeometry(),
					LocalStart,
					StartDir,
					LocalEnd,
					EndDir,
					GetUMGSplineInfo().Thickness,
					DrawEffects,
					TintColor
				);
			}
		}
	}
}

void SUMGSpline::PaintSplineCustomVerts(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const
{
	if (GetUMGSplineInfo().GetPointNum() > 1)
	{
		const TArray<FUMGSplinePoint>& Points = GetUMGSplineInfo().GetPoints();
		const FPaintGeometry& PaintGeometry = AllottedGeometry.ToPaintGeometry();
		PaintGeometry.CommitTransformsIfUsingLegacyConstructor();
		const FSlateRenderTransform& SlateRenderTransform = PaintGeometry.GetAccumulatedRenderTransform();

		// 1 is the minimum thickness we support for generating geometry.
		// The shader takes care of sub-pixel line widths.
		// Thickness is given in screenspace, so convert it to local space before proceeding.
		FSlateLayoutTransform LayoutTransform = FSlateLayoutTransform(PaintGeometry.DrawScale, FVector2D(AllottedGeometry.ToPaintGeometry().DrawPosition));

		float InThickness = FMath::Max(1.0f, Inverse(LayoutTransform).GetScale() * GetUMGSplineInfo().Thickness);

		static const float TwoRootTwo = 2 * UE_SQRT_2;

		// Compute the actual size of the line we need based on thickness.
		// Each line segment will be a bit thicker than the line to account
		// for the size of the filter.
		const float LineThickness = (TwoRootTwo + InThickness);

		// Width of the filter size to use for anti-aliasing.
		// Increasing this value will increase the fuzziness of line edges.
		const float FilterScale = 1.0f;
		const float HalfThickness = LineThickness * 0.5f + FilterScale;

		TArray<FSlateVertex> SlateVerts;
		TArray<SlateIndex> Indexes;
		FUMGSplineRenderBatch RenderBatch = FUMGSplineRenderBatch(&SlateVerts, &Indexes);

		FColor TintColor = (InWidgetStyle.GetColorAndOpacityTint() * GetUMGSplineInfo().TintColor).ToFColor(true);

		FUMGLineBuilder SplineBuilder = FUMGLineBuilder(RenderBatch, Points[0].Location, HalfThickness, GetUMGSplineInfo().Thickness, FilterScale, GetUMGSplineInfo().CustomVertsVCoordScale, SlateRenderTransform, TintColor);

		for (int32 i = 0; i < Points.Num() - 1; ++i)
		{
			FVector2D LocalStart = Points[i].Location;
			FVector2D StartDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points[i].Direction;

			FVector2D LocalEnd = Points[i + 1].Location;
			FVector2D EndDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points[i + 1].Direction;

			if ((LocalStart.X != -FLT_MAX) && (LocalStart.Y != -FLT_MAX) && (LocalEnd.X != -FLT_MAX) && (LocalEnd.Y != -FLT_MAX))
			{
				FVector2D P1 = LocalStart + StartDir / 3.0f;
				FVector2D P2 = LocalEnd - EndDir / 3.0f;
				SplineBuilder.BuildBezierGeometry(LocalStart, P1, P2, LocalEnd);
			}
		}

		if (GetUMGSplineInfo().bClosedLoop)
		{
			FVector2D LocalStart = Points.Last().Location;
			FVector2D StartDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points.Last().Direction;

			FVector2D LocalEnd = Points[0].Location;
			FVector2D EndDir = GetUMGSplineInfo().SplineType == EUMGSplineType::Linear ? FVector2D::ZeroVector : Points[0].Direction;

			if ((LocalStart.X != -FLT_MAX) && (LocalStart.Y != -FLT_MAX) && (LocalEnd.X != -FLT_MAX) && (LocalEnd.Y != -FLT_MAX))
			{
				FVector2D P1 = LocalStart + StartDir / 3.0f;
				FVector2D P2 = LocalEnd - EndDir / 3.0f;
				SplineBuilder.BuildBezierGeometry(LocalStart, P1, P2, LocalEnd);
			}

			SplineBuilder.Finish(Points[0].Location, TintColor, true);
		}
		else
		{
			SplineBuilder.Finish(Points.Last().Location, TintColor);
		}


		// Get a brush
		FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(GetUMGSplineInfo().CustomVertsBrush);

		// Draw
		FSlateDrawElement::MakeCustomVerts(OutDrawElements, LayerId, Handle, SlateVerts, Indexes, nullptr, 0, 0);
	}
}
