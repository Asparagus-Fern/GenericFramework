// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Spline2DType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESpline2DCoordinateSpace : uint8
{
	Local,
	Viewport,
	Screen
};

/**
 * 
 */
UENUM(BlueprintType)
enum class ESpline2DType : uint8
{
	Linear UMETA(DisplayName = "Linear"),
	Curve UMETA(DisplayName = "Curve")
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FSpline2DPoint
{
	GENERATED_BODY()

public:
	FSpline2DPoint();
	FSpline2DPoint(FVector2D InLocation, FVector2D InDirection);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D")
	FVector2D Location = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D")
	FVector2D Direction = FVector2D::ZeroVector;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FSpline2DInfo
{
	GENERATED_BODY()

	FSpline2DInfo();
	FSpline2DInfo(bool Init);

public:
	void AddPoint(const FSpline2DPoint& SplinePoint);
	void InsertPoint(const FSpline2DPoint& SplinePoint, int32 Index);
	void DuplicatePoint(int Index);
	void DeletePoint(int Index);
	FSpline2DPoint FindPoint(int Index) const;
	void SetPoint(const FSpline2DPoint& SplinePoint, int32 Index);
	int GetPointNum() const;
	const TArray<FSpline2DPoint>& GetPoints() const;

public:
	/* 样条线类型 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	ESpline2DType SplineType = ESpline2DType::Curve;

	/* 时间总长度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	float Duration = 1.0f;

	/* 宽度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	float Thickness = 1.0f;

	/* 是否闭环 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	bool bClosedLoop = false;

	/* 在游戏内是否绘制样条线 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	bool bDrawSpline = true;

	/* 样条线颜色 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	FLinearColor TintColor = FLinearColor::White;

	/* 当前样条线点 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline2D Info")
	TArray<FSpline2DPoint> Points;

	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(ClampMin=4, UIMin=4, ClampMax=100, UIMax=100), Category="Spline2D Info")
	int32 ReparamStepsPerSegment = 10;

	/* 是否使用Brush绘制样条线 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category="Spline2D Info")
	bool BuildCustomVerts = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta = (EditCondition = "BuildCustomVerts"), Category="Spline2D Info")
	FSlateBrush CustomVertsBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta = (EditCondition = "BuildCustomVerts"), Category="Spline2D Info")
	float CustomVertsVCoordScale = 1.0;
};

/** Notification for FUMGSplineInfo value change */
DECLARE_DELEGATE_OneParam(FOnSpline2DInfoChanged, const FSpline2DInfo&)

/**
 * SplineCurves的2D版本，源码来自 FSplineCurves
 */
USTRUCT()
struct DEVSLATECORE_API FSplineCurves2D
{
	GENERATED_BODY()

public:
	/** Spline built from Vector2D data. */
	UPROPERTY()
	FInterpCurveVector2D Position;

	/** Input: distance along curve, output: parameter that puts you there. */
	UPROPERTY()
	FInterpCurveFloat ReparamTable;

	bool operator==(const FSplineCurves2D& Other) const { return Position == Other.Position; }
	bool operator!=(const FSplineCurves2D& Other) const { return !(*this == Other); }

public:
	/**
	 * Update the spline's internal data according to the passed-in params
	 * @param	SplineInfo					Spline Information
	 * @param	bStationaryEndpoints		Whether the endpoints of the spline are considered stationary when traversing the spline at non-constant velocity.  Essentially this sets the endpoints' tangents to zero vectors.
	 * @param	ReparamStepsPerSegment	Number of steps per spline segment to place in the reparameterization table
	 * @param	bLoopPositionOverride		Whether to override the loop position with LoopPosition
	 * @param	LoopPosition				The loop position to use instead of the last key
	 * @param	Scale2D						The scale2D to override
	 */
	void UpdateSpline(const FSpline2DInfo& SplineInfo, bool bStationaryEndpoints = false, int32 ReparamStepsPerSegment = 10, bool bLoopPositionOverride = false, float LoopPosition = 0.0f, const FVector2D& Scale2D = FVector2D(1.0f));

	/** Returns the length of the specified spline segment up to the parametric value given */
	float GetSegmentLength(const int32 Index, const float Param, bool bClosedLoop = false, const FVector2D& Scale2D = FVector2D(1.0f)) const;

	/** Returns total length along this spline */
	float GetSplineLength() const;
};
