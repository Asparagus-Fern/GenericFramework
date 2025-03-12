// Fill out your copyright notice in the Description page of Project Settings.

#include "SWidget/SSpline2D.h"

#include "Spline2DType.h"
#include "Spline/Spline2DBuilder.h"
#include "Spline/Spline2DRenderBatch.h"

#include "Widgets/SWidget.h"

/* ==================== FUMGSplineSlot ==================== */

void SSpline2D::FSpline2DSlot::Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs)
{
	Value = InArgs._Value.Get(Value);
	TBasicLayoutWidgetSlot<FSpline2DSlot>::Construct(SlotOwner, MoveTemp(InArgs));
}

FVector2D SSpline2D::FSpline2DSlot::GetOffset() const
{
	return Offset;
}

void SSpline2D::FSpline2DSlot::SetOffset(FVector2D InOffset)
{
	if (Offset != InOffset)
	{
		Offset = InOffset;
	}
}

float SSpline2D::FSpline2DSlot::GetValue() const
{
	return Value;
}

void SSpline2D::FSpline2DSlot::SetValue(float InValue)
{
	if (Value != InValue)
	{
		Value = InValue;
	}
}

/* ==================== SUMGSpline ==================== */

FVector2D GetLocationAtTime(const FSplineCurves2D& SplineCurves2D, float Time)
{
	return SplineCurves2D.Position.Eval(SplineCurves2D.ReparamTable.Eval(Time / 1.f * SplineCurves2D.GetSplineLength(), 0.0f), FVector2D::ZeroVector);
}

SSpline2D::SSpline2D()
	: Children(this, GET_MEMBER_NAME_CHECKED(SSpline2D, Children))
{
}

void SSpline2D::Construct(const FArguments& InArgs)
{
	Spline2DInfoAttribute = InArgs._Spline2DInfo;

	SplineCurves2D.UpdateSpline(GetSpline2DInfo());

	TArray<FSpline2DSlot::FSlotArguments>& SlotArguments = const_cast<TArray<FSpline2DSlot::FSlotArguments>&>(InArgs._Slots);
	Children.AddSlots(MoveTemp(SlotArguments));
}

FChildren* SSpline2D::GetChildren()
{
	return &Children;
}

void SSpline2D::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	for (int32 ChildIndex = 0; ChildIndex < Children.Num(); ++ChildIndex)
	{
		const FSpline2DSlot& CurChild = Children[ChildIndex];
		const TSharedRef<SWidget>& CurWidget = CurChild.GetWidget();
		const EVisibility CurVisibility = CurChild.GetWidget()->GetVisibility();

		if (ArrangedChildren.Accepts(CurVisibility))
		{
			FVector2D LocalPosition, LocalAlignment = FVector2D::ZeroVector;
			FVector2D LocalSize = CurWidget->GetDesiredSize();
			FVector2D LocalOffset = CurChild.GetOffset();
			FVector2D SplinePosition = GetLocationAtTime(GetSplineCurves2D(), CurChild.GetValue());

			{
				const EHorizontalAlignment HorizontalAlignment = CurChild.GetHorizontalAlignment();
				const EVerticalAlignment VerticalAlignment = CurChild.GetVerticalAlignment();

				if (HorizontalAlignment == HAlign_Center)
				{
					LocalAlignment.X = -LocalSize.X / 2;
				}
				else if (HorizontalAlignment == HAlign_Right)
				{
					LocalAlignment.X = -LocalSize.X;
				}

				if (VerticalAlignment == VAlign_Center)
				{
					LocalAlignment.Y = -LocalSize.Y / 2;
				}
				else if (VerticalAlignment == VAlign_Bottom)
				{
					LocalAlignment.Y = -LocalSize.Y;
				}
			}

			LocalPosition = SplinePosition + LocalAlignment + LocalOffset;

			ArrangedChildren.AddWidget
			(
				CurVisibility,
				AllottedGeometry.MakeChild
				(
					CurChild.GetWidget(),
					LocalPosition,
					LocalSize
				)
			);
		}
	}
}

FVector2D SSpline2D::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	TArray<FSpline2DPoint> Points = GetSpline2DInfo().Points;

	if (Points.IsEmpty())
	{
		return FVector2D::ZeroVector;
	}

	FVector2D Min = Points[0].Location;
	FVector2D Max = Points[0].Location;

	for (const auto& Point : GetSpline2DInfo().Points)
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

int32 SSpline2D::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 OutLayerId = LayerId;
	const ESlateDrawEffect DrawEffects = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

	/* 绘制样条线 */
	if (GetSpline2DInfo().bDrawSpline)
	{
		OutLayerId++;
		if (Spline2DInfoAttribute.Get().BuildCustomVerts)
		{
			PaintSplineCustomVerts(AllottedGeometry, OutDrawElements, OutLayerId, MyCullingRect, DrawEffects, InWidgetStyle);;
		}
		else
		{
			PaintSplineDefault(AllottedGeometry, OutDrawElements, OutLayerId, MyCullingRect, DrawEffects, InWidgetStyle);
		}
	}

	/* 绘制样条线上的挂载Widget */
	{
		FArrangedChildren ArrangedChildren(EVisibility::Visible);
		{
			ArrangeChildren(AllottedGeometry, ArrangedChildren);
		}

		FPaintArgs NewArgs = Args.WithNewParent(this);
		const bool bChildrenEnabled = ShouldBeEnabled(bParentEnabled);

		for (int32 ChildIndex = 0; ChildIndex < ArrangedChildren.Num(); ++ChildIndex)
		{
			FArrangedWidget& CurArrangedWidget = ArrangedChildren[ChildIndex];
			OutLayerId++;

			CurArrangedWidget.Widget->Paint(
				NewArgs,
				CurArrangedWidget.Geometry,
				MyCullingRect,
				OutDrawElements,
				OutLayerId,
				InWidgetStyle,
				bChildrenEnabled
			);
		}
	}

	return OutLayerId;
}

SSpline2D::FScopedWidgetSlotArguments SSpline2D::AddSlot()
{
	return InsertSlot(INDEX_NONE);
}

SSpline2D::FScopedWidgetSlotArguments SSpline2D::InsertSlot(int32 Index)
{
	return FScopedWidgetSlotArguments(MakeUnique<FSpline2DSlot>(), this->Children, Index);
}

void SSpline2D::RemoveSlot(int32 Index)
{
	if (Index != INDEX_NONE)
	{
		Children.RemoveAt(Index);
	}
	else if (Children.Num() > 0)
	{
		Children.RemoveAt(Children.Num() - 1);
	}
	else
	{
		ensureMsgf(false, TEXT("Could not remove slot. There are no slots left."));
	}
}

bool SSpline2D::RemoveSlot(TSharedRef<SWidget> Widget)
{
	return Children.Remove(Widget) != INDEX_NONE;
}

void SSpline2D::ClearChildren()
{
	Children.Empty();
}

int32 SSpline2D::GetNumWidgets() const
{
	return Children.Num();
}

SSpline2D::FSpline2DSlot::FSlotArguments SSpline2D::Slot()
{
	return FSpline2DSlot::FSlotArguments(MakeUnique<FSpline2DSlot>());
}

FSplineCurves2D SSpline2D::GetSplineCurves2D() const
{
	return SplineCurves2D;
}

FSpline2DInfo SSpline2D::GetSpline2DInfo() const
{
	return Spline2DInfoAttribute.Get();
}

void SSpline2D::SetSpline2DInfo(TAttribute<FSpline2DInfo> InSpline2DInfo)
{
	Spline2DInfoAttribute = InSpline2DInfo;
	SplineCurves2D.UpdateSpline(GetSpline2DInfo());
}

void SSpline2D::PaintSplineDefault(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const
{
	if (GetSpline2DInfo().GetPointNum() > 1)
	{
		const FColor TintColor = (InWidgetStyle.GetColorAndOpacityTint() * GetSpline2DInfo().TintColor).ToFColor(true);
		const TArray<FSpline2DPoint>& Points = GetSpline2DInfo().GetPoints();

		for (int32 i = 0; i < Points.Num() - 1; ++i)
		{
			FVector2D LocalStart = Points[i].Location;
			FVector2D StartDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points[i].Direction;

			FVector2D LocalEnd = Points[i + 1].Location;
			FVector2D EndDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points[i + 1].Direction;

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
					GetSpline2DInfo().Thickness,
					DrawEffects,
					TintColor
				);
			}
		}

		if (GetSpline2DInfo().bClosedLoop)
		{
			const FVector2D LocalStart = Points.Last().Location;
			const FVector2D StartDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points.Last().Direction;

			const FVector2D LocalEnd = Points[0].Location;
			const FVector2D EndDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points[0].Direction;

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
					GetSpline2DInfo().Thickness,
					DrawEffects,
					TintColor
				);
			}
		}
	}
}

void SSpline2D::PaintSplineCustomVerts(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const
{
	if (GetSpline2DInfo().GetPointNum() > 1)
	{
		const TArray<FSpline2DPoint>& Points = GetSpline2DInfo().GetPoints();
		const FPaintGeometry& PaintGeometry = AllottedGeometry.ToPaintGeometry();
		PaintGeometry.CommitTransformsIfUsingLegacyConstructor();
		const FSlateRenderTransform& SlateRenderTransform = PaintGeometry.GetAccumulatedRenderTransform();

		// 1 is the minimum thickness we support for generating geometry.
		// The shader takes care of sub-pixel line widths.
		// Thickness is given in screenspace, so convert it to local space before proceeding.
		FSlateLayoutTransform LayoutTransform = FSlateLayoutTransform(PaintGeometry.DrawScale, FVector2D(AllottedGeometry.ToPaintGeometry().DrawPosition));

		float InThickness = FMath::Max(1.0f, Inverse(LayoutTransform).GetScale() * GetSpline2DInfo().Thickness);

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
		FSpline2DRenderBatch RenderBatch = FSpline2DRenderBatch(&SlateVerts, &Indexes);

		FColor TintColor = (InWidgetStyle.GetColorAndOpacityTint() * GetSpline2DInfo().TintColor).ToFColor(true);

		FSpline2DBuilder SplineBuilder = FSpline2DBuilder(RenderBatch, Points[0].Location, HalfThickness, GetSpline2DInfo().Thickness, FilterScale, GetSpline2DInfo().CustomVertsVCoordScale, SlateRenderTransform, TintColor);

		for (int32 i = 0; i < Points.Num() - 1; ++i)
		{
			FVector2D LocalStart = Points[i].Location;
			FVector2D StartDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points[i].Direction;

			FVector2D LocalEnd = Points[i + 1].Location;
			FVector2D EndDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points[i + 1].Direction;

			if ((LocalStart.X != -FLT_MAX) && (LocalStart.Y != -FLT_MAX) && (LocalEnd.X != -FLT_MAX) && (LocalEnd.Y != -FLT_MAX))
			{
				FVector2D P1 = LocalStart + StartDir / 3.0f;
				FVector2D P2 = LocalEnd - EndDir / 3.0f;
				SplineBuilder.BuildBezierGeometry(LocalStart, P1, P2, LocalEnd);
			}
		}

		if (GetSpline2DInfo().bClosedLoop)
		{
			FVector2D LocalStart = Points.Last().Location;
			FVector2D StartDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points.Last().Direction;

			FVector2D LocalEnd = Points[0].Location;
			FVector2D EndDir = GetSpline2DInfo().SplineType == ESpline2DType::Linear ? FVector2D::ZeroVector : Points[0].Direction;

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
		FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(GetSpline2DInfo().CustomVertsBrush);

		// Draw
		FSlateDrawElement::MakeCustomVerts(OutDrawElements, LayerId, Handle, SlateVerts, Indexes, nullptr, 0, 0);
	}
}
