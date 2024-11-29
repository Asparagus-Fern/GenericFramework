// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDALType.h"
#include "UObject/Object.h"
#include "GDALDate.generated.h"

class UGDALLayer;
class UGDALSpatialReference;
class UGDALRasterBand;
class GDALDataset;

/**
 * GDALDataset For Unreal(Read Only)
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UGDALDate : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Initialize(FString InDataPath, GDALDataset* InDataSource);
	virtual void Deinitialize();

	FString GetDataPath() const { return DataPath; }
	GDALDataset* GetDataSource() const { return DataSource; }

public:
	/* Fetch raster width in pixels. */
	UFUNCTION(BlueprintPure)
	int32 GetRasterXSize() const;

	/* Fetch raster height in pixels. */
	UFUNCTION(BlueprintPure)
	int32 GetRasterYSize() const;

	/* Fetch the number of raster bands on this dataset. */
	UFUNCTION(BlueprintPure)
	int32 GetRasterCount() const;

	/**
	 * Fetch a band object for a dataset.
	 * @param Index the index number of the band to fetch, from 1 to GetRasterCount().
	 * @return the nBandId th band object
	 */
	UFUNCTION(BlueprintPure)
	UGDALRasterBand* GetRasterBand(int32 Index);

	/**
	 * Flush all write cached data to disk.
	 * @param bAtClosing  Whether this is called from a GDALDataset destructor
	 */
	UFUNCTION(BlueprintCallable)
	void FlushCache(bool bAtClosing = false);

	/* Fetch the spatial reference for this dataset. */
	UFUNCTION(BlueprintPure)
	UGDALSpatialReference* GetSpatialReference();

	/* Fetch the projection definition string for this dataset. */
	UFUNCTION(BlueprintPure)
	FString GetProjection() const;

	/**
	 * Fetches the coefficients for transforming between pixel/line (P,L) raster space, and projection coordinates (Xp,Yp) space.
	 * Xp = GetGeoTransformX().X + P*GetGeoTransformX().Y + L*GetGeoTransformX().Z;
	 */
	UFUNCTION(BlueprintPure)
	FVector GetGeoTransformX() const;

	/**
	 * Fetches the coefficients for transforming between pixel/line (P,L) raster space, and projection coordinates (Xp,Yp) space.
	 * Yp = GetGeoTransformY().X + P*GetGeoTransformY().Y + L*GetGeoTransformY().Z;
	 */
	UFUNCTION(BlueprintPure)
	FVector GetGeoTransformY() const;

	/* Return driver name. */
	UFUNCTION(BlueprintPure)
	FString GetDriverName() const;

	/* Get output spatial reference system for GCPs. */
	UFUNCTION(BlueprintPure)
	UGDALSpatialReference* GetGCPSpatialRef();

	/* Get number of GCPs. */
	UFUNCTION(BlueprintPure)
	int32 GetGCPCount() const;

	/* Fetch GCPs. */
	UFUNCTION(BlueprintPure)
	FGDALGCP GetGCPs() const;

	/* Get output projection for GCPs. */
	UFUNCTION(BlueprintPure)
	FString GetGCPProjection() const;

	/* Adds a mask band to the dataset. */
	UFUNCTION(BlueprintCallable)
	bool CreateMaskBand(int32 nFlagsIn);

	/* Get the number of layers in this dataset. */
	UFUNCTION(BlueprintPure)
	int32 GetLayerCount() const;

	/* Fetch a layer by index. */
	UFUNCTION(BlueprintPure)
	UGDALLayer* GetLayerByIndex(int32 Index);

	/* Returns true if the layer at the specified index is deemed a private or system table, or an internal detail only. */
	UFUNCTION(BlueprintPure)
	bool IsLayerPrivate(int32 Index) const;

	/* Fetch a layer by name. */
	UFUNCTION(BlueprintPure)
	UGDALLayer* GetLayerByName(const FString& Name);

	/* Fetch reference count. */
	UFUNCTION(BlueprintPure)
	int32 GetRefCount() const;

public:
	UFUNCTION(BlueprintPure)
	TArray<UGDALLayer*> GetLayers() { return Layers; }

private:
	FString DataPath;
	GDALDataset* DataSource = nullptr;

	UPROPERTY()
	TArray<UGDALRasterBand*> RasterBands;

	UPROPERTY()
	UGDALSpatialReference* SpatialReference = nullptr;

	UPROPERTY()
	UGDALSpatialReference* GCPSpatialReference = nullptr;

	UPROPERTY()
	TArray<UGDALLayer*> Layers;
};
