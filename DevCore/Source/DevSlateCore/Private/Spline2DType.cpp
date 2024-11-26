// Fill out your copyright notice in the Description page of Project Settings.

#include "..\Public\Spline2DType.h"

/* ==================== FUMGSplinePoint ==================== */

FSpline2DPoint::FSpline2DPoint()
{
}

FSpline2DPoint::FSpline2DPoint(FVector2D InLocation, FVector2D InDirection)
	: Location(InLocation),
	  Direction(InDirection)
{
}

/* ==================== FUMGSplineInfo ==================== */

FSpline2DInfo::FSpline2DInfo()
{
}

FSpline2DInfo::FSpline2DInfo(bool Init)
{
	if (Init)
	{
		Points.Add(FSpline2DPoint(FVector2D(0.0f, 0.0f), FVector2D(200.0f, 0.0f)));
		Points.Add(FSpline2DPoint(FVector2D(200.0f, 200.0f), FVector2D(200.0f, 0.0f)));

		SplineType = ESpline2DType::Curve;
	}
}

void FSpline2DInfo::AddPoint(const FSpline2DPoint& SplinePoint)
{
	Points.Add(SplinePoint);
}

void FSpline2DInfo::InsertPoint(const FSpline2DPoint& SplinePoint, int32 Index)
{
	if (Index >= 0 && Index < Points.Num())
	{
		Points.Insert(SplinePoint, Index);
	}
}

void FSpline2DInfo::DuplicatePoint(int Index)
{
	if (Index >= 0 && Index < Points.Num())
	{
		const FSpline2DPoint NewUMGSplinePoint = FindPoint(Index);
		InsertPoint(NewUMGSplinePoint, Index);
	}
}

void FSpline2DInfo::DeletePoint(int Index)
{
	if (Points.IsValidIndex(Index))
	{
		Points.RemoveAt(Index);
	}
}

FSpline2DPoint FSpline2DInfo::FindPoint(int Index) const
{
	if (Points.IsValidIndex(Index))
	{
		return Points[Index];
	}
	return FSpline2DPoint();
}

void FSpline2DInfo::SetPoint(const FSpline2DPoint& SplinePoint, int32 Index)
{
	if (Index >= 0 && Index < Points.Num())
	{
		Points[Index] = SplinePoint;
	}
}

int FSpline2DInfo::GetPointNum() const
{
	return Points.Num();
}

const TArray<FSpline2DPoint>& FSpline2DInfo::GetPoints() const
{
	return Points;
}

/* ==================== FUMGSplineCurves ==================== */

EInterpCurveMode ConvertUMGSplineTypeToInterpCurveMode(ESpline2DType SplineType)
{
	switch (SplineType)
	{
	case ESpline2DType::Linear: return CIM_Linear;
	case ESpline2DType::Curve: return CIM_CurveUser;

	default: return CIM_Unknown;
	}
}

void FSplineCurves2D::UpdateSpline(const FSpline2DInfo& SplineInfo, bool bStationaryEndpoints, int32 ReparamStepsPerSegment, bool bLoopPositionOverride, float LoopPosition, const FVector2D& Scale2D)
{
	EInterpCurveMode CurveMode = ConvertUMGSplineTypeToInterpCurveMode(SplineInfo.SplineType);
	Position.Points.Reset(SplineInfo.Points.Num());

	for (int32 Index = 0; Index < SplineInfo.Points.Num(); Index++)
	{
		Position.Points.Emplace(Index, SplineInfo.Points[Index].Location, SplineInfo.Points[Index].Direction, SplineInfo.Points[Index].Direction, CurveMode);
	}

	const int32 NumPoints = Position.Points.Num();
	const bool bClosedLoop = SplineInfo.bClosedLoop;

	// Ensure splines' looping status matches with that of the spline widget
	if (bClosedLoop)
	{
		const float LastKey = Position.Points.Num() > 0 ? Position.Points.Last().InVal : 0.0f;
		const float LoopKey = bLoopPositionOverride ? LoopPosition : LastKey + 1.0f;
		Position.SetLoopKey(LoopKey);
	}
	else
	{
		Position.ClearLoopKey();
	}

	// Automatically set the tangents on any CurveAuto keys
	Position.AutoSetTangents(0.0f, bStationaryEndpoints);

	// Now initialize the SplineReParamTable
	const int32 NumSegments = bClosedLoop ? NumPoints : NumPoints - 1;

	// Start by clearing it
	ReparamTable.Points.Reset(NumSegments * ReparamStepsPerSegment + 1);
	float AccumulatedLength = 0.0f;
	for (int32 SegmentIndex = 0; SegmentIndex < NumSegments; ++SegmentIndex)
	{
		for (int32 Step = 0; Step < ReparamStepsPerSegment; ++Step)
		{
			const float Param = static_cast<float>(Step) / ReparamStepsPerSegment;
			const float SegmentLength = (Step == 0) ? 0.0f : GetSegmentLength(SegmentIndex, Param, bClosedLoop, Scale2D);

			ReparamTable.Points.Emplace(SegmentLength + AccumulatedLength, SegmentIndex + Param, 0.0f, 0.0f, CIM_Linear);
		}
		AccumulatedLength += GetSegmentLength(SegmentIndex, 1.0f, bClosedLoop, Scale2D);
	}

	ReparamTable.Points.Emplace(AccumulatedLength, static_cast<float>(NumSegments), 0.0f, 0.0f, CIM_Linear);
}

float FSplineCurves2D::GetSegmentLength(const int32 Index, const float Param, bool bClosedLoop, const FVector2D& Scale2D) const
{
	const int32 NumPoints = Position.Points.Num();
	const int32 LastPoint = NumPoints - 1;

	check(Index >= 0 && ((bClosedLoop && Index < NumPoints) || (!bClosedLoop && Index < LastPoint)));
	check(Param >= 0.0f && Param <= 1.0f);

	// Evaluate the length of a Hermite spline segment.
	// This calculates the integral of |dP/dt| dt, where P(t) is the spline equation with components (x(t), y(t), z(t)).
	// This isn't solvable analytically, so we use a numerical method (Legendre-Gauss quadrature) which performs very well
	// with functions of this type, even with very few samples.  In this case, just 5 samples is sufficient to yield a
	// reasonable result.

	struct FLegendreGaussCoefficient
	{
		float Abscissa;
		float Weight;
	};

	static const FLegendreGaussCoefficient LegendreGaussCoefficients[] =
	{
		{0.0f, 0.5688889f},
		{-0.5384693f, 0.47862867f},
		{0.5384693f, 0.47862867f},
		{-0.90617985f, 0.23692688f},
		{0.90617985f, 0.23692688f}
	};

	const auto& StartPoint = Position.Points[Index];
	const auto& EndPoint = Position.Points[Index == LastPoint ? 0 : Index + 1];

	const auto& P0 = StartPoint.OutVal;
	const auto& T0 = StartPoint.LeaveTangent;
	const auto& P1 = EndPoint.OutVal;
	const auto& T1 = EndPoint.ArriveTangent;

	// Special cases for linear or constant segments
	if (StartPoint.InterpMode == CIM_Linear)
	{
		return ((P1 - P0) * Scale2D).Size() * Param;
	}
	else if (StartPoint.InterpMode == CIM_Constant)
	{
		return 0.0f;
	}

	// Cache the coefficients to be fed into the function to calculate the spline derivative at each sample point as they are constant.
	const FVector2D Coeff1 = ((P0 - P1) * 2.0f + T0 + T1) * 3.0f;
	const FVector2D Coeff2 = (P1 - P0) * 6.0f - T0 * 4.0f - T1 * 2.0f;
	const FVector2D Coeff3 = T0;

	const float HalfParam = Param * 0.5f;

	float Length = 0.0f;
	for (const auto& LegendreGaussCoefficient : LegendreGaussCoefficients)
	{
		// Calculate derivative at each Legendre-Gauss sample, and perform a weighted sum
		const float Alpha = HalfParam * (1.0f + LegendreGaussCoefficient.Abscissa);
		const FVector2D Derivative = ((Coeff1 * Alpha + Coeff2) * Alpha + Coeff3) * Scale2D;
		Length += Derivative.Size() * LegendreGaussCoefficient.Weight;
	}
	Length *= HalfParam;

	return Length;
}

float FSplineCurves2D::GetSplineLength() const
{
	const int32 NumPoints = ReparamTable.Points.Num();

	if (NumPoints > 0)
	{
		return ReparamTable.Points.Last().InVal;
	}

	return 0.0f;
}
