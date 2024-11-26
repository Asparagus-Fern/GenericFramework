// Fill out your copyright notice in the Description page of Project Settings.

#include "UWidget/Spline2D.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Engine/World.h"
#include "Materials/MaterialInterface.h"
#include "SWidget/SSpline2D.h"
#include "UWidget/Spline2DSlot.h"

/* ==================== USpline2D ==================== */

const FInterpCurvePointVector2D USpline2D::DummyPointPosition(0.0f, FVector2D::ZeroVector, FVector2D::ZeroVector, FVector2D::ZeroVector, CIM_Constant);

TSharedRef<SWidget> USpline2D::RebuildWidget()
{
	Spline = SNew(SSpline2D)
		.Spline2DInfo_UObject(this, &USpline2D::GetSplineInfo);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (USpline2DSlot* TypedSlot = Cast<USpline2DSlot>(PanelSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(Spline.ToSharedRef());
		}
	}

	return Spline.ToSharedRef();
}

void USpline2D::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	UpdateSpline();
}

void USpline2D::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	Spline.Reset();
}

UClass* USpline2D::GetSlotClass() const
{
	return USpline2DSlot::StaticClass();
}

void USpline2D::OnSlotAdded(UPanelSlot* InSlot)
{
	if (Spline.IsValid())
	{
		CastChecked<USpline2DSlot>(InSlot)->BuildSlot(Spline.ToSharedRef());
	}
}

void USpline2D::OnSlotRemoved(UPanelSlot* InSlot)
{
	if (Spline.IsValid())
	{
		const TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
		if (Widget.IsValid())
		{
			Spline->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

USpline2DSlot* USpline2D::AddChildToSpline2D(UWidget* Content)
{
	return Cast<USpline2DSlot>(Super::AddChild(Content));
}


/* ==================== Common ==================== */

void USpline2D::UpdateSpline()
{
	SplineCurves.UpdateSpline(SplineInfo);
	if (Spline.IsValid())
	{
		Spline->SetSpline2DInfo(SplineInfo);
	}
}

void USpline2D::AddSplinePoint(const FSpline2DPoint& SplinePoint, bool bUpdateSpline)
{
	SplineInfo.AddPoint(SplinePoint);

	if (bUpdateSpline)
	{
		UpdateSpline();
	}
}

void USpline2D::AddSplinePointAtIndex(const FSpline2DPoint& SplinePoint, int32 Index, bool bUpdateSpline)
{
	SplineInfo.InsertPoint(SplinePoint, Index);

	if (bUpdateSpline)
	{
		UpdateSpline();
	}
}

void USpline2D::ChangeSplinePointAtIndex(const FSpline2DPoint& SplinePoint, int32 Index, bool bUpdateSpline)
{
	SplineInfo.SetPoint(SplinePoint, Index);

	if (bUpdateSpline)
	{
		UpdateSpline();
	}
}

void USpline2D::RemoveSplinePoint(int32 Index, bool bUpdateSpline)
{
	SplineInfo.DeletePoint(Index);

	if (bUpdateSpline)
	{
		UpdateSpline();
	}
}

void USpline2D::RemoveAllSplinePoint(bool bUpdateSpline)
{
	SplineInfo.Points.Empty();

	if (bUpdateSpline)
	{
		UpdateSpline();
	}
}

int32 USpline2D::GetNumberOfSplinePoints() const
{
	return SplineInfo.Points.Num();
}

int32 USpline2D::GetNumberOfSplineSegments() const
{
	const int32 NumPoints = SplineCurves.Position.Points.Num();
	return (SplineInfo.bClosedLoop ? NumPoints : FMath::Max(0, NumPoints - 1));
}

float USpline2D::GetSplineLength() const
{
	return SplineCurves.GetSplineLength();
}

/* ==================== Input Key ==================== */

FVector2D USpline2D::GetLocationAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FVector2D Location = SplineCurves.Position.Eval(InKey, FVector2D::ZeroVector);

	if (CoordinateSpace == ESpline2DCoordinateSpace::Screen)
	{
		return GetCachedGeometry().LocalToAbsolute(Location);
	}
	else if (CoordinateSpace == ESpline2DCoordinateSpace::Viewport)
	{
		FVector2D PixelPosition, ViewportPosition;
		USlateBlueprintLibrary::LocalToViewport(GetWorld(), GetCachedGeometry(), Location, PixelPosition, ViewportPosition);
		return ViewportPosition;
	}

	return Location;
}

FVector2D USpline2D::GetTangentAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FVector2D Tangent = SplineCurves.Position.EvalDerivative(InKey, FVector2D::ZeroVector);

	if (CoordinateSpace == ESpline2DCoordinateSpace::Screen || CoordinateSpace == ESpline2DCoordinateSpace::Viewport)
	{
		return GetCachedGeometry().GetAccumulatedRenderTransform().TransformVector(Tangent);
	}
	return Tangent;
}

FVector2D USpline2D::GetDirectionAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FVector2D Direction = SplineCurves.Position.EvalDerivative(InKey, FVector2D::ZeroVector).GetSafeNormal();

	if (CoordinateSpace == ESpline2DCoordinateSpace::Screen || CoordinateSpace == ESpline2DCoordinateSpace::Viewport)
	{
		return GetCachedGeometry().GetAccumulatedRenderTransform().TransformVector(Direction);
	}

	return Direction;
}

float USpline2D::GetRotationAngleAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FVector2D Direction = GetDirectionAtSplineInputKey(InKey, CoordinateSpace);
	const float AngleInRadians = Direction.IsNearlyZero() ? 0.0f : FMath::Atan2(Direction.Y, Direction.X);

	return FMath::RadiansToDegrees(AngleInRadians);
}

float USpline2D::GetDistanceAlongSplineAtSplineInputKey(float InKey) const
{
	const int32 NumPoints = SplineCurves.Position.Points.Num();
	const int32 NumSegments = SplineInfo.bClosedLoop ? NumPoints : NumPoints - 1;

	if ((InKey >= 0) && (InKey < NumSegments))
	{
		const int32 PointIndex = FMath::FloorToInt(InKey);
		const float Fraction = InKey - PointIndex;
		const int32 ReparamPointIndex = PointIndex * SplineInfo.ReparamStepsPerSegment;
		const float Distance = SplineCurves.ReparamTable.Points[ReparamPointIndex].InVal;
		return Distance + SplineCurves.GetSegmentLength(PointIndex, Fraction, SplineInfo.bClosedLoop, FVector2D(1.0f));;
	}
	else if (InKey >= NumSegments)
	{
		return SplineCurves.GetSplineLength();
	}

	return 0.0f;
}

float USpline2D::GetInputKeyValueAtSplinePoint(int32 PointIndex) const
{
	const FInterpCurvePointVector2D& SplinePoint = GetPositionPointSafe(PointIndex);
	return SplinePoint.InVal;
}

/* ==================== Point Index ==================== */

FVector2D USpline2D::GetLocationAtSplinePoint(int32 PointIndex, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FInterpCurvePointVector2D& Point = GetPositionPointSafe(PointIndex);
	const FVector2D& Location = Point.OutVal;

	if (CoordinateSpace == ESpline2DCoordinateSpace::Screen)
	{
		return GetCachedGeometry().LocalToAbsolute(Location);
	}
	else if (CoordinateSpace == ESpline2DCoordinateSpace::Viewport)
	{
		FVector2D PixelPosition, ViewportPosition;
		USlateBlueprintLibrary::LocalToViewport(GetWorld(), GetCachedGeometry(), Location, PixelPosition, ViewportPosition);
		return ViewportPosition;
	}

	return Location;
}

FVector2D USpline2D::GetDirectionAtSplinePoint(int32 PointIndex, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FInterpCurvePointVector2D& Point = GetPositionPointSafe(PointIndex);
	const FVector2D Direction = Point.LeaveTangent.GetSafeNormal();

	if (CoordinateSpace == ESpline2DCoordinateSpace::Screen || CoordinateSpace == ESpline2DCoordinateSpace::Viewport)
	{
		return GetCachedGeometry().GetAccumulatedRenderTransform().TransformVector(Direction);
	}

	return Direction;
}

FVector2D USpline2D::GetTangentAtSplinePoint(int32 PointIndex, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const FInterpCurvePointVector2D& Point = GetPositionPointSafe(PointIndex);
	const FVector2D& Direction = Point.LeaveTangent;

	if (CoordinateSpace == ESpline2DCoordinateSpace::Screen || CoordinateSpace == ESpline2DCoordinateSpace::Viewport)
	{
		return GetCachedGeometry().GetAccumulatedRenderTransform().TransformVector(Direction);
	}

	return Direction;
}

FVector2D USpline2D::GetArriveTangentAtSplinePoint(int32 PointIndex) const
{
	const FInterpCurvePointVector2D& Point = GetPositionPointSafe(PointIndex);
	return Point.ArriveTangent;
}

FVector2D USpline2D::GetLeaveTangentAtSplinePoint(int32 PointIndex) const
{
	const FInterpCurvePointVector2D& Point = GetPositionPointSafe(PointIndex);
	return Point.LeaveTangent;
}

float USpline2D::GetDistanceAlongSplineAtSplinePoint(int32 PointIndex) const
{
	const int32 NumPoints = SplineCurves.Position.Points.Num();
	const int32 NumSegments = SplineInfo.bClosedLoop ? NumPoints : NumPoints - 1;

	// Ensure that if the reparam table is not prepared yet we don't attempt to access it. This can happen
	// early in the construction of the spline component object.
	if ((PointIndex >= 0) && (PointIndex < NumSegments + 1) && ((PointIndex * SplineInfo.ReparamStepsPerSegment) < SplineCurves.ReparamTable.Points.Num()))
	{
		return SplineCurves.ReparamTable.Points[PointIndex * SplineInfo.ReparamStepsPerSegment].InVal;
	}

	return 0.0f;
}

/* ==================== Time ==================== */

FVector2D USpline2D::GetLocationAtTime(float Time, ESpline2DCoordinateSpace CoordinateSpace, bool bUseConstantVelocity) const
{
	if (SplineInfo.Duration == 0.0f)
	{
		return FVector2D::ZeroVector;
	}

	if (bUseConstantVelocity)
	{
		return GetLocationAtDistanceAlongSpline(Time / SplineInfo.Duration * GetSplineLength(), CoordinateSpace);
	}
	else
	{
		const int32 NumPoints = SplineCurves.Position.Points.Num();
		const int32 NumSegments = SplineInfo.bClosedLoop ? NumPoints : NumPoints - 1;
		const float TimeMultiplier = NumSegments / SplineInfo.Duration;
		return GetLocationAtSplineInputKey(Time * TimeMultiplier, CoordinateSpace);
	}
}

FVector2D USpline2D::GetDirectionAtTime(float Time, ESpline2DCoordinateSpace CoordinateSpace, bool bUseConstantVelocity) const
{
	if (SplineInfo.Duration == 0.0f)
	{
		return FVector2D::ZeroVector;
	}

	if (bUseConstantVelocity)
	{
		return GetDirectionAtDistanceAlongSpline(Time / SplineInfo.Duration * GetSplineLength(), CoordinateSpace);
	}
	else
	{
		const int32 NumPoints = SplineCurves.Position.Points.Num();
		const int32 NumSegments = SplineInfo.bClosedLoop ? NumPoints : NumPoints - 1;
		const float TimeMultiplier = NumSegments / SplineInfo.Duration;
		return GetDirectionAtSplineInputKey(Time * TimeMultiplier, CoordinateSpace);
	}
}

FVector2D USpline2D::GetTangentAtTime(float Time, ESpline2DCoordinateSpace CoordinateSpace, bool bUseConstantVelocity) const
{
	if (SplineInfo.Duration == 0.0f)
	{
		return FVector2D::ZeroVector;
	}

	if (bUseConstantVelocity)
	{
		return GetTangentAtDistanceAlongSpline(Time / SplineInfo.Duration * GetSplineLength(), CoordinateSpace);
	}
	else
	{
		const int32 NumPoints = SplineCurves.Position.Points.Num();
		const int32 NumSegments = SplineInfo.bClosedLoop ? NumPoints : NumPoints - 1;
		const float TimeMultiplier = NumSegments / SplineInfo.Duration;
		return GetTangentAtSplineInputKey(Time * TimeMultiplier, CoordinateSpace);
	}
}

/* ==================== DistanceAlongSpline ==================== */

float USpline2D::GetTimeAtDistanceAlongSpline(float Distance) const
{
	const int32 NumPoints = SplineCurves.Position.Points.Num();

	if (NumPoints < 2)
	{
		return 0.0f;
	}

	return SplineCurves.ReparamTable.Eval(Distance, 0.0f);
}

FVector2D USpline2D::GetLocationAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const float Param = SplineCurves.ReparamTable.Eval(Distance, 0.0f);
	return GetLocationAtSplineInputKey(Param, CoordinateSpace);
}

FVector2D USpline2D::GetDirectionAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const float Param = SplineCurves.ReparamTable.Eval(Distance, 0.0f);
	return GetDirectionAtSplineInputKey(Param, CoordinateSpace);
}

FVector2D USpline2D::GetTangentAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const float Param = SplineCurves.ReparamTable.Eval(Distance, 0.0f);
	return GetTangentAtSplineInputKey(Param, CoordinateSpace);
}

float USpline2D::GetRotationAngleAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const
{
	const float Param = SplineCurves.ReparamTable.Eval(Distance, 0.0f);
	return GetRotationAngleAtSplineInputKey(Param, CoordinateSpace);
}

const FInterpCurvePointVector2D& USpline2D::GetPositionPointSafe(int32 PointIndex) const
{
	const TArray<FInterpCurvePointVector2D>& Points = SplineCurves.Position.Points;
	const int32 NumPoints = Points.Num();
	if (NumPoints > 0)
	{
		const int32 ClampedIndex = (SplineInfo.bClosedLoop && PointIndex >= NumPoints) ? 0 : FMath::Clamp(PointIndex, 0, NumPoints - 1);
		return Points[ClampedIndex];
	}
	else
	{
		return DummyPointPosition;
	}
}
