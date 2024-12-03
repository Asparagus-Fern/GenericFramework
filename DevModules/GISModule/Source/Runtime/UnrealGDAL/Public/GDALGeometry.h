// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDALType.h"
#include "UObject/Object.h"
#include "GDALGeometry.generated.h"

class OGRGeometry;


/**
 * 
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UGDALGeometry : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(OGRGeometry* InDataSource);
	virtual void Deinitialize();

	OGRGeometry* GetDataSource() const { return DataSource; }

public:
	/* Returns TRUE (non-zero) if the object has no points. */
	UFUNCTION(BlueprintPure)
	bool IsEmpty() const;

	/* Returns whether the geometry has a Z component. */
	UFUNCTION(BlueprintPure)
	bool Is3D() const;

	/* Test if the geometry is a ring. */
	UFUNCTION(BlueprintPure)
	bool IsRing() const;

	UFUNCTION(BlueprintPure)
	FString GetGeometryName() const;

	UFUNCTION(BlueprintPure)
	FGDALGeometryType GetGeometryType() const;

	UFUNCTION(BlueprintPure)
	TArray<FVector> GetGeoCoordinate();

public:
	UFUNCTION(BlueprintPure)
	TArray<FPointCoordinate> GetPointCoordinate() const;

	UFUNCTION(BlueprintPure)
	TArray<FVector> GetMultiPointCoordinate() const;

	UFUNCTION(BlueprintPure)
	TArray<FVector> GetLineCoordinate() const;

	UFUNCTION(BlueprintPure)
	TArray<FVector> GetMultiLineCoordinate() const;

private:
	OGRGeometry* DataSource = nullptr;
	FVector GetPointCoordinateInternal(OGRPoint* InPoint){return }
};
