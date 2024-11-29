// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALRasterBand.h"

void UGDALRasterBand::Initialize(GDALRasterBand* InDataSource)
{
	DataSource = InDataSource;
}

void UGDALRasterBand::Deinitialize()
{
}
