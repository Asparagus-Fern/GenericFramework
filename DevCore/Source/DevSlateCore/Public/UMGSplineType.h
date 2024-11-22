// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMGSplineType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUMGSplineType : uint8
{
	Linear UMETA(DisplayName = "Linear"),
	Curve UMETA(DisplayName = "Curve")
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FUMGSplinePoint
{
	GENERATED_BODY()

public:
	FUMGSplinePoint();
	FUMGSplinePoint(FVector2D InLocation, FVector2D InDirection);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Direction;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FUMGSplineInfo
{
	GENERATED_BODY()

	FUMGSplineInfo();
	FUMGSplineInfo(bool Init);

public:
	void AddPoint(const FUMGSplinePoint& SplinePoint);
	void InsertPoint(const FUMGSplinePoint& SplinePoint, int32 Index);
	void DuplicatePoint(int Index);
	void DeletePoint(int Index);
	FUMGSplinePoint FindPoint(int Index) const;
	void SetPoint(const FUMGSplinePoint& SplinePoint, int32 Index);
	int GetPointNum() const;
	const TArray<FUMGSplinePoint>& GetPoints() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUMGSplineType SplineType = EUMGSplineType::Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bClosedLoop = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FUMGSplinePoint> Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay)
	bool BuildCustomVerts = false;

	/** The image/material used for the custom verts spline geometry*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta = (EditCondition = "BuildCustomVerts"))
	FSlateBrush CustomVertsBrush;

	/** The uv.v scale for the custom verts spline geometry*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta = (EditCondition = "BuildCustomVerts"))
	float CustomVertsVCoordScale = 1.0;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVSLATECORE_API FUMGSplineDebugInfo
{
	GENERATED_BODY()

public:
	FUMGSplineDebugInfo();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMGSpline")
	bool bDrawWidgetBoarder = false;

	/** Tint color for this spline */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMGSpline")
	FLinearColor BoarderColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
};

/** Notification for FUMGSplineInfo value change */
DECLARE_DELEGATE_OneParam(FOnSplineInfoValueChanged, const FUMGSplineInfo&)
