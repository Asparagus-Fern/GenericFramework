// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALGeometry.h"

void UGDALGeometry::Initialize(OGRGeometry* InDataSource)
{
	DataSource = InDataSource;
}

void UGDALGeometry::Deinitialize()
{
}
