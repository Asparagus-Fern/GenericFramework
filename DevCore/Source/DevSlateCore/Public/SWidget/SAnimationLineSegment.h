// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLineSegment.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DEVSLATECORE_API SAnimationLineSegment : public SLineSegment
{
	// SLATE_DECLARE_WIDGET_API(SAnimationLineSegment, SLineSegment, DEVSLATECORE_API)

public:
	SLATE_BEGIN_ARGS(SAnimationLineSegment)
			: _Thickness(1.f),
			  _LineColor(FLinearColor::White),
			  _Duration(0.5f),
			  _CurveType(ESequenceTransitionCurve::Linear)
		{
		}

		SLATE_ARGUMENT(float, Thickness)
		SLATE_ARGUMENT(FVector2D, Offset)
		SLATE_ARGUMENT(FLinearColor, LineColor)
		SLATE_ARGUMENT(TArray<FLineSegmentPoint>, LinePoint)
		SLATE_DEFAULT_SLOT(FArguments, Content)

		SLATE_ARGUMENT(float, Duration)
		SLATE_ARGUMENT(ESequenceTransitionCurve, CurveType)
		SLATE_EVENT(FSimpleDelegate, OnTransitionFinish)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:
	void SetTransition(float Duration, ESequenceTransitionCurve Curve);
	void SetTransition(float Duration, ESequenceTransitionCurve Curve, bool PlayForward);
	void PlayTransition(bool PlayForward);

protected:
	bool bIsTransitionTimerRegistered = false;
	TSharedPtr<FActiveTimerHandle> TimerHandle;
	FCurveSequence TransitionSequence;
	FSimpleDelegate OnTransitionFinish;

	EActiveTimerReturnType UpdateTransition(double InCurrentTime, float InDeltaTime);
};
