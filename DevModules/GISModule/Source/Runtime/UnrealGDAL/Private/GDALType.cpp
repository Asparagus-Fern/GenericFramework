// Fill out your copyright notice in the Description page of Project Settings.

#include "GDALType.h"


FGDALGeometryType::FGDALGeometryType()
{
}

FGDALGeometryType::FGDALGeometryType(EGDALGeometryType InGDALGeometryType, bool InSupportZ, bool InSupportM, bool InSupport25D)
	: GDALGeometryType(InGDALGeometryType),
	  bSupportZ(InSupportZ),
	  bSupportM(InSupportM),
	  bSupport25D(InSupport25D)
{
}
