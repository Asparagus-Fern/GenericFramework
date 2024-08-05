// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidget/SAnimationLineSegment.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAnimationLineSegment::Construct(const FArguments& InArgs)
{
	SLineSegment::Construct(SLineSegment::FArguments()
		.Thickness(InArgs._Thickness)
		.Offset(InArgs._Offset)
		.LineColor(InArgs._LineColor)
		.LinePoint(InArgs._LinePoint)
		[
			InArgs._Content.Widget
		]
	);

	OnTransitionFinish = InArgs._OnTransitionFinish;
	SetTransition(InArgs._Duration, InArgs._CurveType);
}

int32 SAnimationLineSegment::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (TransitionSequence.IsPlaying())
	{
		const TArray<FVector2D> Points = CalculatePoints(TransitionSequence.GetLerp());
		FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), Points, ESlateDrawEffect::None, LineColor, true, Thickness);
		LayerId++;
		return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}
	else
	{
		return SLineSegment::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	}
}

void SAnimationLineSegment::SetTransition(float Duration, ESequenceTransitionCurve Curve)
{
	TransitionSequence = FCurveSequence(0.f, Duration, ConvertToCurveEaseFunction(Curve));
}

void SAnimationLineSegment::SetTransition(float Duration, ESequenceTransitionCurve Curve, bool PlayForward)
{
	SetTransition(Duration, Curve);
	PlayTransition(PlayForward);
}

void SAnimationLineSegment::PlayTransition(bool PlayForward)
{
	if (PlayForward)
	{
		TransitionSequence.Play(AsShared());
	}
	else
	{
		TransitionSequence.PlayReverse(AsShared());
	}

	if (!bIsTransitionTimerRegistered)
	{
		bIsTransitionTimerRegistered = true;
		TimerHandle = RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &SAnimationLineSegment::UpdateTransition));
	}
}

EActiveTimerReturnType SAnimationLineSegment::UpdateTransition(double InCurrentTime, float InDeltaTime)
{
	if (!TransitionSequence.IsPlaying())
	{
		bIsTransitionTimerRegistered = false;
		UnRegisterActiveTimer(TimerHandle.ToSharedRef());
		OnTransitionFinish.ExecuteIfBound();

		return EActiveTimerReturnType::Stop;
	}

	return EActiveTimerReturnType::Continue;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
