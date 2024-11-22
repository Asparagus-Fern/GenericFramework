// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGSplineType.h"

FUMGSplinePoint::FUMGSplinePoint()
{
}

FUMGSplinePoint::FUMGSplinePoint(FVector2D InLocation, FVector2D InDirection)
	: Location(InLocation),
	  Direction(InDirection)
{
}

FUMGSplineInfo::FUMGSplineInfo()
{
}

FUMGSplineInfo::FUMGSplineInfo(bool Init)
{
	if (Init)
	{
		Points.Add(FUMGSplinePoint(FVector2D(0.0f, 0.0f), FVector2D(200.0f, 0.0f)));
		Points.Add(FUMGSplinePoint(FVector2D(200.0f, 200.0f), FVector2D(200.0f, 0.0f)));

		SplineType = EUMGSplineType::Curve;
	}
}

void FUMGSplineInfo::AddPoint(const FUMGSplinePoint& SplinePoint)
{
	Points.Add(SplinePoint);
}

void FUMGSplineInfo::InsertPoint(const FUMGSplinePoint& SplinePoint, int32 Index)
{
	if (Index >= 0 && Index < Points.Num())
	{
		Points.Insert(SplinePoint, Index);
	}
}

void FUMGSplineInfo::DuplicatePoint(int Index)
{
	if (Index >= 0 && Index < Points.Num())
	{
		const FUMGSplinePoint NewUMGSplinePoint = FindPoint(Index);
		InsertPoint(NewUMGSplinePoint, Index);
	}
}

void FUMGSplineInfo::DeletePoint(int Index)
{
	if (Points.IsValidIndex(Index))
	{
		Points.RemoveAt(Index);
	}
}

FUMGSplinePoint FUMGSplineInfo::FindPoint(int Index) const
{
	if (Points.IsValidIndex(Index))
	{
		return Points[Index];
	}
	return FUMGSplinePoint();
}

void FUMGSplineInfo::SetPoint(const FUMGSplinePoint& SplinePoint, int32 Index)
{
	if (Index >= 0 && Index < Points.Num())
	{
		Points[Index] = SplinePoint;
	}
}

int FUMGSplineInfo::GetPointNum() const
{
	return Points.Num();
}

const TArray<FUMGSplinePoint>& FUMGSplineInfo::GetPoints() const
{
	return Points;
}

FUMGSplineDebugInfo::FUMGSplineDebugInfo()
{
}
