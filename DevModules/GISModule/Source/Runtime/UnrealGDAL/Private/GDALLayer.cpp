// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALLayer.h"

#include "GDALFeature.h"
#include "GDALFeatureDefinition.h"
#include "ogrsf_frmts.h"

void UGDALLayer::Initialize(OGRLayer* InDataSource)
{
	DataSource = InDataSource;

	FeatureDefinition = NewObject<UGDALFeatureDefinition>(this);
	FeatureDefinition->Initialize(DataSource->GetLayerDefn());

	for (auto FeatureIt = 0; FeatureIt < DataSource->GetFeatureCount(); FeatureIt++)
	{
		UGDALFeature* NewFeature = NewObject<UGDALFeature>(this);
		NewFeature->Initialize(DataSource->GetFeature(FeatureIt));
		Features.Add(NewFeature);
	}
}

void UGDALLayer::Deinitialize()
{
	for (const auto& Feature : Features)
	{
		Feature->Deinitialize();
	}

	FeatureDefinition->Deinitialize();
}

FString UGDALLayer::GetLayerName() const
{
	return DataSource->GetName();
}

FGDALGeometryType UGDALLayer::GetGeometryType() const
{
	return ConvToGDALGeometryType(DataSource->GetGeomType());
}

int32 UGDALLayer::GetFeatureCount() const
{
	return Features.Num();
}

UGDALFeature* UGDALLayer::GetFeature(int64 ID)
{
	for (const auto& Feature : Features)
	{
		if (Feature->GetDataSource()->GetFID() == static_cast<long long>(ID))
		{
			return Feature;
		}
	}

	return nullptr;
}
