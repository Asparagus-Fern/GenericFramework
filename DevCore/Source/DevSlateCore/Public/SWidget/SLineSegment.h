// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Widgets/SCompoundWidget.h"



/**
 * 
 */
class DEVSLATECORE_API SLineSegment : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLineSegment)
			: _Thickness(1.f),
			  _Offset(0.f, 0.f),
			  _LineColor(FLinearColor::White)
		{
		}

		SLATE_ARGUMENT(float, Thickness)
		SLATE_ARGUMENT(FVector2D, Offset)
		SLATE_ARGUMENT(FLinearColor, LineColor)
		SLATE_ARGUMENT(TArray<FLineSegmentPoint>, LinePoint)
		SLATE_DEFAULT_SLOT(FArguments, Content)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:
	virtual TArray<FVector2D> CalculatePoints() const;
	virtual TArray<FVector2D> CalculatePoints(float Alpha) const;
	virtual FVector2D CalculatePoint(FLineSegmentPoint InLinePoint) const;
	float GetLineSegmentLength() const;

protected:
	float Thickness = 0.f;
	FVector2D Offset = FVector2D::Zero();
	FLinearColor LineColor = FLinearColor::White;
	TArray<FLineSegmentPoint> LinePoints;
	TSharedPtr<SWidget> Content;

public:
	float GetThickness() const { return Thickness; }
	FVector2D GetOffset() const { return Offset; }
	FLinearColor GetLineColor() const { return LineColor; }
	TArray<FLineSegmentPoint> GetLinePoints() const { return LinePoints; }
	TSharedRef<SWidget> GetContent() const { return Content.IsValid() ? Content.ToSharedRef() : SNullWidget::NullWidget; }

	void SetThickness(float InThickness);
	void SetOffset(FVector2D InOffset);
	void SetLineColor(FLinearColor InLineColor);
	void SetLinePoints(const TArray<FLineSegmentPoint>& InLinePoints);
	void SetContent(const TSharedRef<SWidget>& InContent);
};
