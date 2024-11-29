// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALFeature.h"

#include "GDALGeometry.h"
#include "ogr_feature.h"

void UGDALFeature::Initialize(OGRFeature* InDataSource)
{
	DataSource = InDataSource;

	Geometry = NewObject<UGDALGeometry>(this);
	Geometry->Initialize(DataSource->GetGeometryRef());
}

void UGDALFeature::Deinitialize()
{
}