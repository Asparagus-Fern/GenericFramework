// Fill out your copyright notice in the Description page of Project Settings.


#include "UWidget/AnimationLineSegment.h"

#include "SWidget/SAnimationLineSegment.h"
#include "UWidget/LineSegmentSlot.h"

TSharedRef<SWidget> UAnimationLineSegment::RebuildWidget()
{
	MyLineSegment = SNew(SAnimationLineSegment)
		.Thickness(Thickness)
		.Offset(Offset)
		.LineColor(LineColor)
		.LinePoint(LinePoints)
		.Duration(Duration)
		.CurveType(CurveType);

	if (GetChildrenCount() > 0)
	{
		Cast<ULineSegmentSlot>(GetContentSlot())->BuildSlot(MyLineSegment.ToSharedRef());
	}

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	return MyLineSegment.ToSharedRef();
}

float UAnimationLineSegment::GetDuration() const
{
	return Duration;
}

void UAnimationLineSegment::SetDuration(const float InDuration)
{
	Duration = InDuration;
	if (MyLineSegment.IsValid())
	{
		StaticCastSharedPtr<SAnimationLineSegment>(MyLineSegment)->SetTransition(Duration, CurveType);
	}
}

ESequenceTransitionCurve UAnimationLineSegment::GetCurveType() const
{
	return CurveType;
}

void UAnimationLineSegment::SetCurveType(const ESequenceTransitionCurve InCurveType)
{
	CurveType = InCurveType;
	if (MyLineSegment.IsValid())
	{
		StaticCastSharedPtr<SAnimationLineSegment>(MyLineSegment)->SetTransition(Duration, CurveType);
	}
}

void UAnimationLineSegment::PlayTransition(const bool PlayForward)
{
	if (MyLineSegment.IsValid())
	{
		StaticCastSharedPtr<SAnimationLineSegment>(MyLineSegment)->PlayTransition(PlayForward);
	}
}

void UAnimationLineSegment::HandleTransitionFinish()
{
	OnTransitionFinish.Broadcast();
}
