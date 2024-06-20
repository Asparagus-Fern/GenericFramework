// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateWidgetType.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATEWIDGETGENERATION_API SLine : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLine)
			: _Anchor(0.f, 0.f),
			  _Thickness(1.f),
			  _LineColor(FLinearColor::White)
		{
		}

		SLATE_ARGUMENT(FVector2D, Anchor)
		SLATE_ARGUMENT(float, Thickness)
		SLATE_ARGUMENT(FLinearColor, LineColor)
		SLATE_ARGUMENT(TArray<FLinePoint>, LinePoint)
		SLATE_DEFAULT_SLOT(FArguments, Content)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;

protected:
	virtual TArray<FVector2D> CalculatePoints() const;
	virtual FVector2D CalculatePoint(FLinePoint InLinePoint) const;

protected:
	FVector2D Anchor = FVector2D::Zero();
	float Thickness = 1.f;
	FLinearColor LineColor;
	TArray<FLinePoint> LinePoints;
	TSharedPtr<SWidget> Content;

public:
	FVector2D GetAnchor() const { return Anchor; }
	float GetThickness() const { return Thickness; }
	FLinearColor GetLineColor() const { return LineColor; }
	TArray<FLinePoint> GetLinePoints() const { return LinePoints; }

	void SetAnchor(FVector2D InAnchor);
	void SetThickness(float InThickness);
	void SetLineColor(FLinearColor InLineColor);
	void SetLinePoints(const TArray<FLinePoint>& InLinePoints);

	void SetContent(const TSharedRef<SWidget>& InContent);
};
