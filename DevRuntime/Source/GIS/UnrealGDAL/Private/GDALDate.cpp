// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALDate.h"

#include "GDALLayer.h"
#include "GDALRasterBand.h"
#include "GDALSpatialReference.h"
#include "Windows/PreWindowsApi.h"
#include "gdal_priv.h"
#include "Windows/PostWindowsApi.h"

UGDALDate::UGDALDate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGDALDate::Initialize(FString InDataPath, GDALDataset* InDataSource)
{
	DataPath = InDataPath;
	DataSource = InDataSource;

	for (auto FieldIt = 0; FieldIt < DataSource->GetLayerCount(); FieldIt++)
	{
		UGDALLayer* NewLayer = NewObject<UGDALLayer>(this);
		NewLayer->Initialize(DataSource->GetLayer(FieldIt));
		Layers.Add(NewLayer);
	}
}

void UGDALDate::Deinitialize()
{
	for (const auto& Layer : Layers)
	{
		Layer->Deinitialize();
	}

	if (IsValid(GCPSpatialReference))
	{
		GCPSpatialReference->Deinitialize();
	}

	if (IsValid(SpatialReference))
	{
		SpatialReference->Deinitialize();
	}

	for (const auto& RasterBand : RasterBands)
	{
		RasterBand->Deinitialize();
	}

	if (DataSource)
	{
		GDALClose(DataSource);
	}
}

int32 UGDALDate::GetRasterXSize() const
{
	return DataSource->GetRasterXSize();
}

int32 UGDALDate::GetRasterYSize() const
{
	return DataSource->GetRasterYSize();
}

int32 UGDALDate::GetRasterCount() const
{
	return DataSource->GetRasterCount();
}

UGDALRasterBand* UGDALDate::GetRasterBand(int32 Index)
{
	if (GDALRasterBand* GdalRasterBand = DataSource->GetRasterBand(Index))
	{
		if (UGDALRasterBand** Found = RasterBands.FindByPredicate([GdalRasterBand](const UGDALRasterBand* GDALRasterBand)
			{
				return GdalRasterBand == GDALRasterBand->GetDataSource();
			}
		))
		{
			return *Found;
		}

		UGDALRasterBand* NewRaterBand = NewObject<UGDALRasterBand>(this);
		NewRaterBand->Initialize(GdalRasterBand);
		RasterBands.Add(NewRaterBand);

		return NewRaterBand;
	}

	return nullptr;
}

void UGDALDate::FlushCache(bool bAtClosing)
{
	DataSource->FlushCache(bAtClosing);
}

UGDALSpatialReference* UGDALDate::GetSpatialReference()
{
	if (IsValid(SpatialReference))
	{
		return SpatialReference;
	}

	const OGRSpatialReference* OGRSpatialReference = DataSource->GetSpatialRef();
	SpatialReference = NewObject<UGDALSpatialReference>(this);
	SpatialReference->Initialize(OGRSpatialReference);

	return SpatialReference;
}

FString UGDALDate::GetProjection() const
{
	return DataSource->GetProjectionRef();
}

FVector UGDALDate::GetGeoTransformX() const
{
	double GeoTransform[6];
	DataSource->GetGeoTransform(GeoTransform);

	return FVector(GeoTransform[0], GeoTransform[1], GeoTransform[2]);
}

FVector UGDALDate::GetGeoTransformY() const
{
	double GeoTransform[6];
	DataSource->GetGeoTransform(GeoTransform);

	return FVector(GeoTransform[3], GeoTransform[4], GeoTransform[5]);
}

FString UGDALDate::GetDriverName() const
{
	return DataSource->GetDriverName();
}

UGDALSpatialReference* UGDALDate::GetGCPSpatialRef()
{
	if (IsValid(GCPSpatialReference))
	{
		return GCPSpatialReference;
	}

	const OGRSpatialReference* OGRSpatialReference = DataSource->GetGCPSpatialRef();
	GCPSpatialReference = NewObject<UGDALSpatialReference>(this);
	GCPSpatialReference->Initialize(OGRSpatialReference);

	return SpatialReference;
}

int32 UGDALDate::GetGCPCount() const
{
	return DataSource->GetGCPCount();
}

FGDALGCP UGDALDate::GetGCPs() const
{
	const GDAL_GCP* Source = DataSource->GetGCPs();
	FGDALGCP GCP = FGDALGCP();

	if (Source)
	{
		GCP.Id = Source->pszId;
		GCP.Info = Source->pszInfo;
		GCP.GCPLine = Source->dfGCPLine;
		GCP.GCPPixel = Source->dfGCPPixel;
		GCP.GCPX = Source->dfGCPX;
		GCP.GCPY = Source->dfGCPY;
		GCP.GCPZ = Source->dfGCPZ;
	}

	return GCP;
}

FString UGDALDate::GetGCPProjection() const
{
	return DataSource->GetGCPProjection();
}

bool UGDALDate::CreateMaskBand(int32 nFlagsIn)
{
	return DataSource->CreateMaskBand(nFlagsIn) != CE_Failure;
}

int32 UGDALDate::GetLayerCount() const
{
	return DataSource->GetLayerCount();
}

UGDALLayer* UGDALDate::GetLayerByIndex(int32 Index)
{
	if (OGRLayer* ORGLayer = DataSource->GetLayer(Index))
	{
		if (UGDALLayer** Found = Layers.FindByPredicate([ORGLayer](const UGDALLayer* GDALLayer)
			{
				return ORGLayer == GDALLayer->GetDataSource();
			}
		))
		{
			return *Found;
		}

		UGDALLayer* NewLayer = NewObject<UGDALLayer>(this);
		NewLayer->Initialize(ORGLayer);
		Layers.Add(NewLayer);

		return NewLayer;
	}

	return nullptr;
}

bool UGDALDate::IsLayerPrivate(int32 Index) const
{
	return DataSource->IsLayerPrivate(Index);
}

UGDALLayer* UGDALDate::GetLayerByName(const FString& Name)
{
	if (OGRLayer* Layer = DataSource->GetLayerByName(TCHAR_TO_UTF8(*Name)))
	{
		if (UGDALLayer** Found = Layers.FindByPredicate([Layer](const UGDALLayer* GDALLayer)
			{
				return Layer == GDALLayer->GetDataSource();
			}
		))
		{
			return *Found;
		}

		UGDALLayer* NewLayer = NewObject<UGDALLayer>(this);
		NewLayer->Initialize(Layer);
		Layers.Add(NewLayer);

		return NewLayer;
	}

	return nullptr;
}

int32 UGDALDate::GetRefCount() const
{
	return DataSource->GetRefCount();
}
