// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GeoReferencingSystem.h"
#include "GeographicCoordinates.h"
#include "Windows/MinWindows.h"

#include "Windows/PreWindowsApi.h"
#include "gdal_priv.h"
#include "ogrsf_frmts.h"
#include "Windows/PostWindowsApi.h"

#include "GDALType.generated.h"

/* ==================== EGDALError ==================== */

UENUM(BlueprintType)
enum class EGDALError : uint8
{
	/* Success */
	Success,

	/* Not enough data to deserialize */
	Not_Enough_Data,

	/* Not enough memory */
	Not_Enough_Memory,

	/* Unsupported geometry type */
	Unsupported_Geometry_Type,

	/* Unsupported operation */
	Unsupported_Operation,

	/* Corrupt data */
	Corrupt_Data,

	/* Failure */
	Failure,

	/* Unsupported SRS */
	Unsupported_Srs,

	/* Invalid handle */
	Invalid_Handle,

	/* Non existing feature */
	Non_Existing_Feature,
};

inline EGDALError ConvToGDALError(OGRErr OGRError)
{
	if (OGRError == OGRERR_NONE)
	{
		return EGDALError::Success;
	}
	else if (OGRError == OGRERR_NOT_ENOUGH_DATA)
	{
		return EGDALError::Not_Enough_Data;
	}
	else if (OGRError == OGRERR_NOT_ENOUGH_MEMORY)
	{
		return EGDALError::Not_Enough_Memory;
	}
	else if (OGRError == OGRERR_UNSUPPORTED_GEOMETRY_TYPE)
	{
		return EGDALError::Unsupported_Geometry_Type;
	}
	else if (OGRError == OGRERR_UNSUPPORTED_OPERATION)
	{
		return EGDALError::Unsupported_Operation;
	}
	else if (OGRError == OGRERR_CORRUPT_DATA)
	{
		return EGDALError::Corrupt_Data;
	}
	else if (OGRError == OGRERR_FAILURE)
	{
		return EGDALError::Failure;
	}
	else if (OGRError == OGRERR_UNSUPPORTED_SRS)
	{
		return EGDALError::Unsupported_Srs;
	}
	else if (OGRError == OGRERR_INVALID_HANDLE)
	{
		return EGDALError::Invalid_Handle;
	}
	else if (OGRError == OGRERR_NON_EXISTING_FEATURE)
	{
		return EGDALError::Non_Existing_Feature;
	}

	return EGDALError::Failure;
}

inline OGRErr ConvToOGRError(EGDALError GDALError)
{
	switch (GDALError)
	{
	case EGDALError::Success:
		return OGRERR_NONE;
	case EGDALError::Not_Enough_Data:
		return OGRERR_NOT_ENOUGH_DATA;
	case EGDALError::Not_Enough_Memory:
		return OGRERR_NOT_ENOUGH_MEMORY;
	case EGDALError::Unsupported_Geometry_Type:
		return OGRERR_UNSUPPORTED_GEOMETRY_TYPE;
	case EGDALError::Unsupported_Operation:
		return OGRERR_UNSUPPORTED_OPERATION;
	case EGDALError::Corrupt_Data:
		return OGRERR_CORRUPT_DATA;
	case EGDALError::Failure:
		return OGRERR_FAILURE;
	case EGDALError::Unsupported_Srs:
		return OGRERR_UNSUPPORTED_SRS;
	case EGDALError::Invalid_Handle:
		return OGRERR_INVALID_HANDLE;
	case EGDALError::Non_Existing_Feature:
		return OGRERR_NON_EXISTING_FEATURE;
	}

	return OGRERR_FAILURE;
}

/* ==================== FGDALGCP ==================== */

USTRUCT(BlueprintType)
struct FGDALGCP
{
	GENERATED_BODY()

public:
	/** Unique identifier, often numeric */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Id;

	/** Informational message or "" */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Info;

	/** Pixel (x) location of GCP on raster */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double GCPPixel;

	/** Line (y) location of GCP on raster */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double GCPLine;

	/** X position of GCP in georeferenced space */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double GCPX;

	/** Y position of GCP in georeferenced space */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double GCPY;

	/** Elevation of GCP, or zero if not known */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double GCPZ;
};

/* ==================== FGDALGeometryType ==================== */

UENUM(BlueprintType)
enum class EGDALGeometryType :uint8
{
	wkbUnknown,
	wkbPoint,
	wkbMultiPoint,
	wkbLineString,
	wkbMultiLineString,
	wkbPolygon,
	wkbMultiPolygon,
	wkbGeometryCollection,

	wkbCurve,
	wkbMultiCurve,
	wkbSurface,
	wkbMultiSurface,

	wkbCircularString,
	wkbCompoundCurve,
	wkbCurvePolygon,
	wkbPolyhedralSurface,
	wkbTIN,
	wkbTriangle,

	wkbLinearRing,
	wkbNone
};

USTRUCT(BlueprintType)
struct FGDALGeometryType
{
	GENERATED_BODY()

public:
	FGDALGeometryType();
	FGDALGeometryType(EGDALGeometryType InGDALGeometryType, bool InSupportZ, bool InSupportM, bool InSupport25D);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGDALGeometryType GDALGeometryType = EGDALGeometryType::wkbUnknown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSupportZ = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSupportM = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSupport25D = false;
};

inline FGDALGeometryType ConvToGDALGeometryType(OGRwkbGeometryType OGRwkbGeometryType)
{
	switch (OGRwkbGeometryType)
	{
	case wkbUnknown:
		return FGDALGeometryType(EGDALGeometryType::wkbUnknown, false, false, false);

	case wkbPoint:
		return FGDALGeometryType(EGDALGeometryType::wkbPoint, false, false, false);

	case wkbLineString:
		return FGDALGeometryType(EGDALGeometryType::wkbLineString, false, false, false);

	case wkbPolygon:
		return FGDALGeometryType(EGDALGeometryType::wkbPolygon, false, false, false);

	case wkbMultiPoint:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPoint, false, false, false);

	case wkbMultiLineString:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiLineString, false, false, false);

	case wkbMultiPolygon:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPolygon, false, false, false);

	case wkbGeometryCollection:
		return FGDALGeometryType(EGDALGeometryType::wkbGeometryCollection, false, false, false);

	case wkbCircularString:
		return FGDALGeometryType(EGDALGeometryType::wkbCircularString, false, false, false);

	case wkbCompoundCurve:
		return FGDALGeometryType(EGDALGeometryType::wkbCompoundCurve, false, false, false);

	case wkbCurvePolygon:
		return FGDALGeometryType(EGDALGeometryType::wkbCurvePolygon, false, false, false);

	case wkbMultiCurve:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiCurve, false, false, false);

	case wkbMultiSurface:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiSurface, false, false, false);

	case wkbCurve:
		return FGDALGeometryType(EGDALGeometryType::wkbCurve, false, false, false);

	case wkbSurface:
		return FGDALGeometryType(EGDALGeometryType::wkbSurface, false, false, false);

	case wkbPolyhedralSurface:
		return FGDALGeometryType(EGDALGeometryType::wkbPolyhedralSurface, false, false, false);

	case wkbTIN:
		return FGDALGeometryType(EGDALGeometryType::wkbTIN, false, false, false);

	case wkbTriangle:
		return FGDALGeometryType(EGDALGeometryType::wkbTriangle, false, false, false);

	case wkbNone:
		return FGDALGeometryType(EGDALGeometryType::wkbNone, false, false, false);

	case wkbLinearRing:
		return FGDALGeometryType(EGDALGeometryType::wkbLinearRing, false, false, false);

	case wkbCircularStringZ:
		return FGDALGeometryType(EGDALGeometryType::wkbCircularString, true, false, false);

	case wkbCompoundCurveZ:
		return FGDALGeometryType(EGDALGeometryType::wkbCompoundCurve, true, false, false);

	case wkbCurvePolygonZ:
		return FGDALGeometryType(EGDALGeometryType::wkbCurvePolygon, true, false, false);

	case wkbMultiCurveZ:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiCurve, true, false, false);

	case wkbMultiSurfaceZ:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiSurface, true, false, false);

	case wkbCurveZ:
		return FGDALGeometryType(EGDALGeometryType::wkbCurve, true, false, false);

	case wkbSurfaceZ:
		return FGDALGeometryType(EGDALGeometryType::wkbSurface, true, false, false);

	case wkbPolyhedralSurfaceZ:
		return FGDALGeometryType(EGDALGeometryType::wkbPolyhedralSurface, true, false, false);

	case wkbTINZ:
		return FGDALGeometryType(EGDALGeometryType::wkbTIN, true, false, false);

	case wkbTriangleZ:
		return FGDALGeometryType(EGDALGeometryType::wkbTriangle, true, false, false);

	case wkbPointM:
		return FGDALGeometryType(EGDALGeometryType::wkbPoint, false, true, false);

	case wkbLineStringM:
		return FGDALGeometryType(EGDALGeometryType::wkbLineString, false, true, false);

	case wkbPolygonM:
		return FGDALGeometryType(EGDALGeometryType::wkbPolygon, false, true, false);

	case wkbMultiPointM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPoint, false, true, false);

	case wkbMultiLineStringM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiLineString, false, true, false);

	case wkbMultiPolygonM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPolygon, false, true, false);

	case wkbGeometryCollectionM:
		return FGDALGeometryType(EGDALGeometryType::wkbGeometryCollection, false, true, false);

	case wkbCircularStringM:
		return FGDALGeometryType(EGDALGeometryType::wkbCircularString, false, true, false);

	case wkbCompoundCurveM:
		return FGDALGeometryType(EGDALGeometryType::wkbCompoundCurve, false, true, false);

	case wkbCurvePolygonM:
		return FGDALGeometryType(EGDALGeometryType::wkbCurvePolygon, false, true, false);

	case wkbMultiCurveM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiCurve, false, true, false);

	case wkbMultiSurfaceM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiSurface, false, true, false);

	case wkbCurveM:
		return FGDALGeometryType(EGDALGeometryType::wkbCurve, false, true, false);

	case wkbSurfaceM:
		return FGDALGeometryType(EGDALGeometryType::wkbSurface, false, true, false);

	case wkbPolyhedralSurfaceM:
		return FGDALGeometryType(EGDALGeometryType::wkbPolyhedralSurface, false, true, false);

	case wkbTINM:
		return FGDALGeometryType(EGDALGeometryType::wkbTIN, false, true, false);

	case wkbTriangleM:
		return FGDALGeometryType(EGDALGeometryType::wkbTriangle, false, true, false);

	case wkbPointZM:
		return FGDALGeometryType(EGDALGeometryType::wkbPoint, true, true, false);

	case wkbLineStringZM:
		return FGDALGeometryType(EGDALGeometryType::wkbLineString, true, true, false);

	case wkbPolygonZM:
		return FGDALGeometryType(EGDALGeometryType::wkbPolygon, true, true, false);

	case wkbMultiPointZM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPoint, true, true, false);

	case wkbMultiLineStringZM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiLineString, true, true, false);

	case wkbMultiPolygonZM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPolygon, true, true, false);

	case wkbGeometryCollectionZM:
		return FGDALGeometryType(EGDALGeometryType::wkbGeometryCollection, true, true, false);

	case wkbCircularStringZM:
		return FGDALGeometryType(EGDALGeometryType::wkbCircularString, true, true, false);

	case wkbCompoundCurveZM:
		return FGDALGeometryType(EGDALGeometryType::wkbCompoundCurve, true, true, false);

	case wkbCurvePolygonZM:
		return FGDALGeometryType(EGDALGeometryType::wkbCurvePolygon, true, true, false);

	case wkbMultiCurveZM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiCurve, true, true, false);

	case wkbMultiSurfaceZM:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiSurface, true, true, false);

	case wkbCurveZM:
		return FGDALGeometryType(EGDALGeometryType::wkbCurve, true, true, false);

	case wkbSurfaceZM:
		return FGDALGeometryType(EGDALGeometryType::wkbSurface, true, true, false);

	case wkbPolyhedralSurfaceZM:
		return FGDALGeometryType(EGDALGeometryType::wkbPolyhedralSurface, true, true, false);

	case wkbTINZM:
		return FGDALGeometryType(EGDALGeometryType::wkbTIN, true, true, false);

	case wkbTriangleZM:
		return FGDALGeometryType(EGDALGeometryType::wkbTriangle, true, true, false);

	case wkbPoint25D:
		return FGDALGeometryType(EGDALGeometryType::wkbPoint, false, false, true);

	case wkbLineString25D:
		return FGDALGeometryType(EGDALGeometryType::wkbLineString, false, false, true);

	case wkbPolygon25D:
		return FGDALGeometryType(EGDALGeometryType::wkbPolygon, false, false, true);

	case wkbMultiPoint25D:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPoint, false, false, true);

	case wkbMultiLineString25D:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiLineString, false, false, true);

	case wkbMultiPolygon25D:
		return FGDALGeometryType(EGDALGeometryType::wkbMultiPolygon, false, false, true);

	case wkbGeometryCollection25D:
		return FGDALGeometryType(EGDALGeometryType::wkbGeometryCollection, false, false, true);
	}

	return FGDALGeometryType();
};

/* ==================== FPointCoordinate ==================== */

USTRUCT(BlueprintType)
struct FPointCoordinate
{
	GENERATED_BODY()

public:
	FPointCoordinate();
	FPointCoordinate(const FVector& InCoordinate);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Coordinate;
};

/* ==================== FMultiPointCoordinate ==================== */

USTRUCT(BlueprintType)
struct FMultiPointCoordinate
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPointCoordinate> PointCoordinates;
};
