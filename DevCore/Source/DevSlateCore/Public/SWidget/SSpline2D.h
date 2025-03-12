// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spline2DType.h"
#include "Framework/SlateDelegates.h"
#include "Layout/ChildrenBase.h"
#include "Widgets/SPanel.h"
#include "Widgets/SLeafWidget.h"

class FSpline2DInterface;

/**
 *
 */
class DEVSLATECORE_API SSpline2D : public SPanel
{
public:
	class DEVSLATECORE_API FSpline2DSlot : public TBasicLayoutWidgetSlot<FSpline2DSlot>
	{
	public:
		FSpline2DSlot()
			: TBasicLayoutWidgetSlot<FSpline2DSlot>(HAlign_Center, VAlign_Center),
			  Offset(FVector2D::ZeroVector),
			  Value(0.f)
		{
		}

		SLATE_SLOT_BEGIN_ARGS(FSpline2DSlot, TBasicLayoutWidgetSlot<FSpline2DSlot>)
			SLATE_ARGUMENT(TOptional<float>, Value)
		SLATE_SLOT_END_ARGS()

		void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs);

		FVector2D GetOffset() const;
		void SetOffset(FVector2D InOffset);

		float GetValue() const;
		void SetValue(float InValue);

	private:
		FVector2D Offset;
		float Value;
	};

	SLATE_BEGIN_ARGS(SSpline2D)
			: _Spline2DInfo()
		{
		}

		SLATE_ATTRIBUTE(FSpline2DInfo, Spline2DInfo)

		SLATE_EVENT(FOnFloatValueChanged, OnValueChanged)

		SLATE_SLOT_ARGUMENT(SSpline2D::FSpline2DSlot, Slots)

	SLATE_END_ARGS()

public:
	SSpline2D();
	void Construct(const FArguments& InArgs);
	virtual FChildren* GetChildren() override;
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:
	using FScopedWidgetSlotArguments = TPanelChildren<FSpline2DSlot>::FScopedWidgetSlotArguments;

	FScopedWidgetSlotArguments AddSlot();
	FScopedWidgetSlotArguments InsertSlot(int32 Index = INDEX_NONE);
	void RemoveSlot(int32 Index);
	bool RemoveSlot(TSharedRef<SWidget> Widget);
	void ClearChildren();
	int32 GetNumWidgets() const;

	static FSpline2DSlot::FSlotArguments Slot();

public:
	FSplineCurves2D GetSplineCurves2D() const;
	FSpline2DInfo GetSpline2DInfo() const;
	void SetSpline2DInfo(TAttribute<FSpline2DInfo> InSpline2DInfo);

protected:
	void PaintSplineDefault(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;
	void PaintSplineCustomVerts(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;

protected:
	FSplineCurves2D SplineCurves2D;
	TAttribute<FSpline2DInfo> Spline2DInfoAttribute;
	TPanelChildren<FSpline2DSlot> Children;
};
