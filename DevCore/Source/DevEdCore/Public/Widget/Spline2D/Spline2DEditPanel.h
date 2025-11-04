// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Framework/SlateDelegates.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "SWidget/Spline2D/Spline2DType.h"

class FPaintArgs;
class FSlateWindowElementList;
struct FSlateBrush;

/**
 * 
 */
struct FSelectedSplineTangent
{
public:
	FSelectedSplineTangent();
	bool IsValid() const;

public:
	int32 PointIndex = -1;
	bool bIsArrial = false;
};

/**
 * 
 */
struct FSplineEditPanelTransform
{
public:
	FSplineEditPanelTransform();
	FVector2D LocalToInput(FVector2D Local) const;
	FVector2D InputToLocal(FVector2D Input) const;

public:
	FVector2D Offset;
	float Scale;
};

/**
 * Edit panel for a spline
 */
class SSpline2DEditPanel : public SCompoundWidget
{
protected:
	/* Represents the different states of a drag operation. Copy from SCurveEditor.h */
	enum class EDragState
	{
		/* The user has clicked a mouse button, but hasn't moved more then the drag threshold. */
		PreDrag,
		/* The user is dragging the selected keys. */
		DragKey,
		/* The user is free dragging the selected keys. */
		FreeDrag,
		/* The user is dragging a selected tangent handle. */
		DragTangent,
		/* The user is panning the curve view. */
		Pan,
		/* The user is zooming the curve view. */
		Zoom,
		/* There is no active drag operation. */
		None
	};

public:
	SLATE_BEGIN_ARGS(SSpline2DEditPanel)
			: _SplineInfo(),
			  _OnSplineInfoValueChanged()
		{
		}

		SLATE_ATTRIBUTE(FSpline2DInfo, SplineInfo)

		SLATE_EVENT(FOnSpline2DInfoChanged, OnSplineInfoValueChanged)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	virtual FVector2D ComputeDesiredSize(float) const override;

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;

	virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:
	/* Paint a spline with engine default draw function*/
	void PaintSpline_Default(const FSpline2DInfo& InSplineInfo, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;

	/* Paint a spline with custom verts draw function*/
	void PaintSpline_CustomVerts(const FSpline2DInfo& InSplineInfo, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;

	/* Paint the keys that make up a curve */
	void PaintSplinePoints(const FSpline2DInfo& InSplineInfo, FSlateWindowElementList& OutDrawElements, int32 LayerId, int32 SelectedLayerId, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, const FWidgetStyle& InWidgetStyle) const;

	/* Paint the tangent for a key with cubic curves */
	void PaintTangent(const FSpline2DPoint& SplinePoint, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects, int32 LayerToUse, const FWidgetStyle& InWidgetStyle, bool bTangentSelected) const;

	/* Paint Grid lines, these make it easier to visualize relative distance */
	void PaintGridLines(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FSlateRect& MyCullingRect, ESlateDrawEffect DrawEffects) const;

	bool IsSplinePointSelected(int PointIndex) const;

	void GetTangentPoints(const FVector2D& Location, const FVector2D& Direction, FVector2D& Arrive, FVector2D& Leave) const;

	/* Attempts to start a drag operation when the mouse moves. */
	void TryStartDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	/* Processes an ongoing drag operation when the mouse moves. */
	void ProcessDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	/* Completes an ongoing drag operation on mouse up. */
	void EndDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	/* Zoom the view. */
	void ZoomView(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	/* Test a screen space location to find which key was clicked on */
	int32 HitTestSplinePoints(const FGeometry& InMyGeometry, const FVector2D& HitScreenPosition);

	/* Test a screen space location to find if any cubic tangents were clicked on */
	FSelectedSplineTangent HitTestCubicTangents(const FGeometry& InMyGeometry, const FVector2D& HitScreenPosition);

	/* Handles a mouse click operation on mouse up */
	void ProcessClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	/* Function to create context menu on mouse right click*/
	void CreateContextMenu(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent, bool bShowAddNewSplinePoint);

	/* Adds a new spline point to the spline. */
	void AddNewSplinePoint(FGeometry InMyGeometry, FVector2D ScreenPosition);

	/* Called by delete command */
	void DeleteSelectedSplinePoint();

	float CalculateGridPixelSpacing() const;

	/* Defered Zoom to fit */
	void DeferredZoomToFit();

	/* Active timer that handles deferred zooming until the target zoom is reached */
	EActiveTimerReturnType HandleZoomToFit(double InCurrentTime, float InDeltaTime);

	/* Zoom to fit */
	bool ZoomToFit(bool bFitHorizontal, bool bFitVertical);

	/* Zoom to fit button clicked*/
	FReply ZoomToFitClicked();

	/* Function to create menu on adjust panel height button click*/
	TSharedRef<SWidget> GetPanelHeightMenu();

	/* Panel height Label callback */
	FText GetPanelHeightLabel() const;

	/* Returns the current panel height setting */
	float GetPanelHeightSliderPosition() const;

	/* Sets new panel height */
	void OnSetPanelHeight(float NewValue);

	/* Function to create menu on spline thickness button click*/
	TSharedRef<SWidget> GetThicknessFillMenu();

	/* Spline Thickness Label callback */
	FText GetSplineThicknessLabel() const;

	/* Returns  the spline thickness */
	float GetSplineThicknessSliderPosition() const;

	/* Sets new Spline Thickness */
	void OnSetSplineThickness(float NewValue);

	/* Returns the help text */
	FText GetHelpText() const;

private:
	TAttribute<FSpline2DInfo> SplineInfo;

	/* The location of mouse during the last OnMouseButtonDown callback in widget local coordinates. */
	FVector2D MouseDownLocation = FVector2D::ZeroVector;

	/* The location of the mouse during the last OnMouseMove callback in widget local coordinates. */
	FVector2D MouseMoveLocation = FVector2D::ZeroVector;

	/* The state of the current drag operation happening with the widget, if any. */
	EDragState DragState = EDragState::None;

	/* The number of pixels which the mouse must move before a drag operation starts. */
	float DragThreshold = 4.f;

	/* A map of selected key handle to their starting locations at the beginning of a drag operation. */
	TMap<int32, FVector2D> PreDragPointLocations;

	/* A map of selected key handles to their tangent values at the beginning of a drag operation. */
	TMap<int32, FVector2D> PreDragTangents;

	FSelectedSplineTangent SelectedTangent;

	int32 DraggedPointIndex = 0;

	int32 SelectedPointIndex = 0;

	FOnSpline2DInfoChanged OnSplineInfoValueChanged;

	FSplineEditPanelTransform TransformInfo;

	bool HideUnselectedTangents = false;

	bool bDeferredZoomToFit = false;

	bool bEditPanelFocus = false;

	TSharedPtr<SImage> HelpIconImage;
};
