// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALGeometry.h"

#include "ogr_geometry.h"

void UGDALGeometry::Initialize(OGRGeometry* InDataSource)
{
	DataSource = InDataSource;
}

void UGDALGeometry::Deinitialize()
{
}

bool UGDALGeometry::IsEmpty() const
{
	return static_cast<bool>(DataSource->IsEmpty());
}

bool UGDALGeometry::Is3D() const
{
	return static_cast<bool>(DataSource->Is3D());
}

bool UGDALGeometry::IsRing() const
{
	return static_cast<bool>(DataSource->IsRing());
}

FString UGDALGeometry::GetGeometryName() const
{
	return UTF8_TO_TCHAR(DataSource->getGeometryName());
}

FGDALGeometryType UGDALGeometry::GetGeometryType() const
{
	return ConvToGDALGeometryType(DataSource->getGeometryType());
}

TArray<FVector> UGDALGeometry::GetGeoCoordinate()
{
	TArray<FVector> Coordinate;
	return Coordinate;
}

TArray<FPointCoordinate> UGDALGeometry::GetPointCoordinate() const
{
	TArray<FPointCoordinate> Coordinate;

	if (const OGRPoint* Point = DataSource->toPoint())
	{
		Coordinate.Add(FPointCoordinate(FVector(Point->getX(), Point->getY(), 0)));
	}

	return Coordinate;
}

TArray<FVector> UGDALGeometry::GetMultiPointCoordinate() const
{
	TArray<FVector> Coordinate;

	if (OGRMultiPoint* MultiPoint = DataSource->toMultiPoint())
	{
		for (auto It = 0; It < MultiPoint->getNumGeometries(); It++)
		{
			const OGRPoint* Point = MultiPoint->getGeometryRef(It);
			Coordinate.Add(FVector(Point->getX(), Point->getY(), 0));
		}
	}

	return Coordinate;
}

TArray<FVector> UGDALGeometry::GetLineCoordinate() const
{
	TArray<FVector> Coordinate;

	if (OGRLineString* Line = DataSource->toLineString())
	{
		for (auto It = 0; It < Line->getNumPoints(); It++)
		{
			OGRPoint* Point = nullptr;
			Line->getPoint(It, Point);

			Coordinate.Add(FVector(Point->getX(), Point->getY(), 0));
		}
	}

	return Coordinate;
}

TArray<FVector> UGDALGeometry::GetMultiLineCoordinate() const
{
	TArray<FVector> Coordinate;

	if (OGRMultiLineString* MultiLine = DataSource->toMultiLineString())
	{
		for (auto MultiLineIt = 0; MultiLineIt < MultiLine->getNumGeometries(); MultiLineIt++)
		{
			OGRLineString* Line = MultiLine->getGeometryRef(MultiLineIt);

			for (auto LineIt = 0; LineIt < Line->getNumPoints(); LineIt++)
			{
				OGRPoint* Point = nullptr;
				Line->getPoint(LineIt, Point);

				Coordinate.Add(FVector(Point->getX(), Point->getY(), 0));
			}
		}
	}

	return Coordinate;
}
