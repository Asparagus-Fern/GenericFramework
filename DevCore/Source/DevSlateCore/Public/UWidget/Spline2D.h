// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Spline2DType.h"

#include "Components/Widget.h"
#include "Components/PanelWidget.h"
#include "Spline2D.generated.h"

class USpline2DSlot;
class SSpline2D;
class UMaterialInterface;

/**
 *
 */
UCLASS()
class DEVSLATECORE_API USpline2D final : public UPanelWidget
{
	GENERATED_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif

protected:
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D")
	FSpline2DInfo SplineInfo = FSpline2DInfo(true);

public:
	FSpline2DInfo GetSplineInfo() const { return SplineInfo; }

	UFUNCTION(BlueprintCallable, Category="Spline2D")
	USpline2DSlot* AddChildToSpline2D(UWidget* Content);

	/* ==================== Common ==================== */
public:
	/* Update the spline tangents and SplineReParamTable */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	void UpdateSpline();

	/* Adds a point to the spline */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	void AddSplinePoint(const FSpline2DPoint& SplinePoint, bool bUpdateSpline);

	/* Adds a point to the spline at the specified index */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	void AddSplinePointAtIndex(const FSpline2DPoint& SplinePoint, int32 Index, bool bUpdateSpline);

	/* Change a point to the spline at the specified index */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	void ChangeSplinePointAtIndex(const FSpline2DPoint& SplinePoint, int32 Index, bool bUpdateSpline);

	/* Removes point at specified index from the spline */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	void RemoveSplinePoint(int32 Index, bool bUpdateSpline);

	/* Removes all points from the spline */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	void RemoveAllSplinePoint(bool bUpdateSpline);

	/* Get the number of points that make up this spline */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	int32 GetNumberOfSplinePoints() const;

	/* Get the number of segments that make up this spline */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	int32 GetNumberOfSplineSegments() const;

	/* Returns total length along this spline */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Common")
	float GetSplineLength() const;

	/* ==================== Input Key ==================== */
public:
	/* Get location along spline at the provided input key value */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Input Key")
	FVector2D GetLocationAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Get tangent along spline at the provided input key value */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Input Key")
	FVector2D GetTangentAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Get unit direction along spline at the provided input key value */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Input Key")
	FVector2D GetDirectionAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Get rotator corresponding to rotation along spline at the provided input key value */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Input Key")
	float GetRotationAngleAtSplineInputKey(float InKey, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Get distance along the spline at the provided input key value */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Input Key")
	float GetDistanceAlongSplineAtSplineInputKey(float InKey) const;

	/* Get the input key (e.g. the time) of the control point of the spline at the specified index. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Input Key")
	float GetInputKeyValueAtSplinePoint(int32 PointIndex) const;

	/* ==================== Point Index ==================== */
public:
	/* Get the location at spline point */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Point Index")
	FVector2D GetLocationAtSplinePoint(int32 PointIndex, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Get the direction at spline point */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Point Index")
	FVector2D GetDirectionAtSplinePoint(int32 PointIndex, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Get the tangent at spline point. This fetches the Leave tangent of the point. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Point Index")
	FVector2D GetTangentAtSplinePoint(int32 PointIndex, ESpline2DCoordinateSpace CoordinateSpace) const;

	UFUNCTION(BlueprintCallable, Category="Spline2D|Point Index")
	FVector2D GetArriveTangentAtSplinePoint(int32 PointIndex) const;

	/* Get the leave tangent at spline point */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Point Index")
	FVector2D GetLeaveTangentAtSplinePoint(int32 PointIndex) const;

	/* Get the distance along the spline at the spline point */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Point Index")
	float GetDistanceAlongSplineAtSplinePoint(int32 PointIndex) const;

	/* ==================== Time ==================== */
public:
	/* Given a time from 0 to the spline duration, return the point in space where this puts you */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Time")
	FVector2D GetLocationAtTime(float Time, ESpline2DCoordinateSpace CoordinateSpace, bool bUseConstantVelocity = false) const;

	/* Given a time from 0 to the spline duration, return a unit direction vector of the spline tangent there. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Time")
	FVector2D GetDirectionAtTime(float Time, ESpline2DCoordinateSpace CoordinateSpace, bool bUseConstantVelocity = false) const;

	/* Given a time from 0 to the spline duration, return the spline's tangent there. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Time")
	FVector2D GetTangentAtTime(float Time, ESpline2DCoordinateSpace CoordinateSpace, bool bUseConstantVelocity = false) const;

	/* ==================== DistanceAlongSpline ==================== */
public:
	/* Given a distance along the length of this spline, return the corresponding input key at that point */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Distance Along Spline")
	float GetTimeAtDistanceAlongSpline(float Distance) const;

	/* Given a distance along the length of this spline, return the point in space where this puts you */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Distance Along Spline")
	FVector2D GetLocationAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Given a distance along the length of this spline, return a unit direction vector of the spline tangent there. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Distance Along Spline")
	FVector2D GetDirectionAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Given a distance along the length of this spline, return the tangent vector of the spline there. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Distance Along Spline")
	FVector2D GetTangentAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const;

	/* Given a distance along the length of this spline, return a rotation corresponding to the spline's rotation there. */
	UFUNCTION(BlueprintCallable, Category="Spline2D|Distance Along Spline")
	float GetRotationAngleAtDistanceAlongSpline(float Distance, ESpline2DCoordinateSpace CoordinateSpace) const;

private:
	/* The dummy value used for queries when there are no point in a spline */
	static const FInterpCurvePointVector2D DummyPointPosition;

	/* Returns a const reference to the specified position point, but gives back a dummy point if there are no points */
	const FInterpCurvePointVector2D& GetPositionPointSafe(int32 PointIndex) const;

private:
	// Shared Ptr to the Spline.
	TSharedPtr<SSpline2D> Spline;

	UPROPERTY(transient)
	FSplineCurves2D SplineCurves;
};
