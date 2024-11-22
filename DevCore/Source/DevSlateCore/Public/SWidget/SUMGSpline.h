// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Core Include
#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"
#include "UMGSplineType.h"

/**
 *
 */
class DEVSLATECORE_API SUMGSpline : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SUMGSpline)
			: _SplineInfo(),
			  _SplineDebugInfo()
		{
		}

		SLATE_ATTRIBUTE(FUMGSplineInfo, SplineInfo)
		SLATE_ATTRIBUTE(FUMGSplineDebugInfo, SplineDebugInfo)

		SLATE_EVENT(FOnLinearColorValueChanged, OnValueChanged)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:
	FUMGSplineInfo GetUMGSplineInfo() const;

protected:
	void PaintWidgetBoarder(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects) const;
	void PaintSplineDefault(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;
	void PaintSplineCustomVerts(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;

private:
	TAttribute<FUMGSplineInfo> SplineInfo;
	TAttribute<FUMGSplineDebugInfo> SplineDebugInfo;
};
