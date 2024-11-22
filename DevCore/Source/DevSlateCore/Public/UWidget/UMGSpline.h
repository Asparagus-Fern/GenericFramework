// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Widget.h"
#include "UMGSplineType.h"
#include "UMGSpline.generated.h"

class SUMGSpline;
class UMaterialInterface;

/**
 * 
 */
UENUM()
namespace EUMGSplineCoordinateSpace
{
	enum Type
	{
		Local,
		Viewport,
		Screen
	};
}

/**
 * 
 */
USTRUCT()
struct DEVSLATECORE_API FUMGSplineCurves
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FInterpCurveVector2D Position;

	UPROPERTY()
	FInterpCurveFloat ReparamTable;

	UPROPERTY(transient)
	int32 ReparamStepsPerSegment;

	bool operator==(const FUMGSplineCurves& Other) const { return Position == Other.Position; }
	bool operator!=(const FUMGSplineCurves& Other) const { return !(*this == Other); }

public:
	/**
	 * Update the spline's internal data according to the passed-in params
	 * @param	SplineInfo					Spline Information
	 * @param	bStationaryEndpoints		Whether the endpoints of the spline are considered stationary when traversing the spline at non-constant velocity.  Essentially this sets the endpoints' tangents to zero vectors.
	 * @param	InReparamStepsPerSegment	Number of steps per spline segment to place in the reparameterization table
	 * @param	bClosedLoopPositionOverride	Whether to override the loop position with LoopPosition
	 * @param	LoopPosition				The loop position to use instead of the last key
	 * @param	Scale2D						The world scale to override
	 */
	void UpdateSpline(const FUMGSplineInfo& SplineInfo, bool bStationaryEndpoints = false, int32 InReparamStepsPerSegment = 10, bool bClosedLoopPositionOverride = false, float LoopPosition = 0.0f, const FVector2D& Scale2D = FVector2D(1.0f));

	/** Returns the length of the specified spline segment up to the parametric value given */
	float GetSegmentLength(const int32 Index, const float Param, bool bClosedLoop = false, const FVector2D& Scale2D = FVector2D(1.0f)) const;

	/** Returns total length along this spline */
	float GetSplineLength() const;
};

/**
 *
 */
UCLASS()
class DEVSLATECORE_API UUMGSpline final : public UWidget
{
	GENERATED_BODY()

protected:
	virtual void OnWidgetRebuilt() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif

public:
	/** Spline Info */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUMGSplineInfo SplineInfo = FUMGSplineInfo(true);

	/** Debug Info */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUMGSplineDebugInfo SplineDebugInfo;

public:
	/** Update the spline tangents and SplineReParamTable */
	UFUNCTION(BlueprintCallable)
	void UpdateSpline();

	/** Get location along spline at the provided input key value */
	UFUNCTION(BlueprintCallable)
	FVector2D GetLocationAtSplineInputKey(float InKey, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Get tangent along spline at the provided input key value */
	UFUNCTION(BlueprintCallable)
	FVector2D GetTangentAtSplineInputKey(float InKey, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Get unit direction along spline at the provided input key value */
	UFUNCTION(BlueprintCallable)
	FVector2D GetDirectionAtSplineInputKey(float InKey, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Get rotator corresponding to rotation along spline at the provided input key value */
	UFUNCTION(BlueprintCallable)
	float GetRotationAngleAtSplineInputKey(float InKey, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Get distance along the spline at the provided input key value */
	UFUNCTION(BlueprintCallable)
	float GetDistanceAlongSplineAtSplineInputKey(float InKey) const;

	/** Adds a point to the spline */
	UFUNCTION(BlueprintCallable)
	void AddSplinePoint(const FUMGSplinePoint& SplinePoint, bool bUpdateSpline);

	/** Adds a point to the spline at the specified index */
	UFUNCTION(BlueprintCallable)
	void AddSplinePointAtIndex(const FUMGSplinePoint& SplinePoint, int32 Index, bool bUpdateSpline);

	/** Change a point to the spline at the specified index */
	UFUNCTION(BlueprintCallable)
	void ChangeSplinePointAtIndex(const FUMGSplinePoint& SplinePoint, int32 Index, bool bUpdateSpline);

	/** Removes point at specified index from the spline */
	UFUNCTION(BlueprintCallable)
	void RemoveSplinePoint(int32 Index, bool bUpdateSpline);

	/** Removes all points from the spline */
	UFUNCTION(BlueprintCallable)
	void RemoveAllSplinePoint(bool bUpdateSpline);

	/** Set spline thickness */
	UFUNCTION(BlueprintCallable)
	void SetSplineThickness(float Thickness);

	/** Get spline thickness */
	UFUNCTION(BlueprintCallable)
	float GetSplineThickness() const;

	/** Set spline material */
	UFUNCTION(BlueprintCallable)
	void SetSplineMaterial(UMaterialInterface* Material);

	/** Get spline material */
	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetSplineMaterial() const;

	/** Get the type of spline */
	UFUNCTION(BlueprintCallable)
	EUMGSplineType GetSplineType() const;

	/** Specify the type of spline */
	UFUNCTION(BlueprintCallable)
	void SetSplineType(EUMGSplineType Type);

	/** Get the number of points that make up this spline */
	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfSplinePoints() const;

	/** Get the location at spline point */
	UFUNCTION(BlueprintCallable)
	FVector2D GetLocationAtSplinePoint(int32 PointIndex, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Get the direction at spline point */
	UFUNCTION(BlueprintCallable)
	FVector2D GetDirectionAtSplinePoint(int32 PointIndex, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Get the tangent at spline point. This fetches the Leave tangent of the point. */
	UFUNCTION(BlueprintCallable)
	FVector2D GetTangentAtSplinePoint(int32 PointIndex, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Returns total length along this spline */
	UFUNCTION(BlueprintCallable)
	float GetSplineLength() const;

	/** Given a distance along the length of this spline, return the corresponding input key at that point */
	UFUNCTION(BlueprintCallable)
	float GetInputKeyAtDistanceAlongSpline(float Distance, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Given a distance along the length of this spline, return the point in space where this puts you */
	UFUNCTION(BlueprintCallable)
	FVector2D GetLocationAtDistanceAlongSpline(float Distance, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Given a distance along the length of this spline, return a unit direction vector of the spline tangent there. */
	UFUNCTION(BlueprintCallable)
	FVector2D GetDirectionAtDistanceAlongSpline(float Distance, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Given a distance along the length of this spline, return the tangent vector of the spline there. */
	UFUNCTION(BlueprintCallable)
	FVector2D GetTangentAtDistanceAlongSpline(float Distance, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

	/** Given a distance along the length of this spline, return a rotation corresponding to the spline's rotation there. */
	UFUNCTION(BlueprintCallable)
	float GetRotationAngleAtDistanceAlongSpline(float Distance, EUMGSplineCoordinateSpace::Type CoordinateSpace) const;

public:
	FUMGSplineInfo GetSplineInfo() const { return SplineInfo; }
	FUMGSplineDebugInfo GetSplineDebugInfo() const { return SplineDebugInfo; }

private:
	/** The dummy value used for queries when there are no point in a spline */
	static const FInterpCurvePointVector2D DummyPointPosition;

	/** Returns a const reference to the specified position point, but gives back a dummy point if there are no points */
	const FInterpCurvePointVector2D& GetPositionPointSafe(int32 PointIndex) const;

private:
	// Shared Ptr to the Spline.
	TSharedPtr<SUMGSpline> Spline;

	UPROPERTY(transient)
	FUMGSplineCurves SplineCurves;
};
