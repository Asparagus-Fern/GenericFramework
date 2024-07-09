// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateWidgetType.h"
#include "Slate/SCommonAnimatedSwitcher.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATEWIDGETGENERATION_API SLine : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLine)
			: _Thickness(1.f),
			  _Duration(0.5f),
			  _Anchor(0.f, 0.f),
			  _LineColor(FLinearColor::White)
		{
		}

		SLATE_ARGUMENT(float, Thickness)
		SLATE_ARGUMENT(float, Duration)
		SLATE_ARGUMENT(ETransitionCurve, CurveType)
		SLATE_ARGUMENT(FVector2D, Anchor)
		SLATE_ARGUMENT(FLinearColor, LineColor)
		SLATE_ARGUMENT(TArray<FLinePoint>, LinePoint)
		SLATE_DEFAULT_SLOT(FArguments, Content)

		SLATE_EVENT(FSimpleDelegate, OnTransitionFinish)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;

protected:
	virtual TArray<FVector2D> CalculatePoints() const;
	virtual TArray<FVector2D> CalculatePoints(float Alpha) const;
	virtual FVector2D CalculatePoint(FLinePoint InLinePoint) const;

protected:
	float Thickness = 1.f;
	FVector2D Anchor = FVector2D::Zero();
	FLinearColor LineColor;
	TArray<FLinePoint> LinePoints;
	TSharedPtr<SWidget> Content;

	bool bIsTransitionTimerRegistered = false;
	FCurveSequence TransitionSequence;
	FSimpleDelegate OnTransitionFinish;

public:
	float GetThickness() const { return Thickness; }
	FVector2D GetAnchor() const { return Anchor; }
	FLinearColor GetLineColor() const { return LineColor; }
	TArray<FLinePoint> GetLinePoints() const { return LinePoints; }

	void SetThickness(float InThickness);
	void SetAnchor(FVector2D InAnchor);
	void SetLineColor(FLinearColor InLineColor);
	void SetLinePoints(const TArray<FLinePoint>& InLinePoints);

	void SetContent(const TSharedRef<SWidget>& InContent);
	void SetTransition(float Duration, ETransitionCurve Curve);

public:
	float GetLength() const;
	void PlayTransition(bool InForward);

protected:
	EActiveTimerReturnType UpdateTransition(double InCurrentTime, float InDeltaTime);
};
