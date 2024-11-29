// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALSpatialReference.h"

void UGDALSpatialReference::Initialize(const OGRSpatialReference* InDataSource)
{
	DataSource = InDataSource;
}

void UGDALSpatialReference::Deinitialize()
{
}
