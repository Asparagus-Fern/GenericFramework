// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALFeatureDefinition.h"

#include "ogr_feature.h"

void UGDALFeatureDefinition::Initialize(OGRFeatureDefn* InDataSource)
{
	FeatureDefinition = InDataSource;

	for (auto FieldIt = 0; FieldIt < FeatureDefinition->GetFieldCount(); FieldIt++)
	{
		Fields.Add(FeatureDefinition->GetFieldDefn(FieldIt));
	}
}

void UGDALFeatureDefinition::Deinitialize()
{
}

FString UGDALFeatureDefinition::GetDefinitionName() const
{
	return FeatureDefinition->GetName();
}

void UGDALFeatureDefinition::SetDefinitionName(FString InName)
{
	FeatureDefinition->SetName(TCHAR_TO_UTF8(*InName));
}

int32 UGDALFeatureDefinition::GetFieldCount() const
{
	return FeatureDefinition->GetFieldCount();
}

FString UGDALFeatureDefinition::GetFieldName(int32 Index)
{
	if (Fields.IsValidIndex(Index))
	{
		return Fields[Index]->GetNameRef();
	}

	ensureMsgf(true, TEXT("Invalid Field"));
	return "";
}

void UGDALFeatureDefinition::SetFieldName(int32 Index, FString InName)
{
	if (Fields.IsValidIndex(Index))
	{
		Fields[Index]->SetName(TCHAR_TO_UTF8(*InName));
	}

	ensureMsgf(true, TEXT("Invalid Field"));
}

FString UGDALFeatureDefinition::GetFieldDefault(int32 Index)
{
	if (Fields.IsValidIndex(Index))
	{
		return Fields[Index]->GetDefault();
	}

	ensureMsgf(true, TEXT("Invalid Field"));
	return "";
}

void UGDALFeatureDefinition::SetFieldDefault(int32 Index, FString InName)
{
	if (Fields.IsValidIndex(Index))
	{
		Fields[Index]->SetDefault(TCHAR_TO_UTF8(*InName));
	}

	ensureMsgf(true, TEXT("Invalid Field"));
}

int32 UGDALFeatureDefinition::GetFieldIndex(FString InName) const
{
	return FeatureDefinition->GetFieldIndex(TCHAR_TO_UTF8(*InName));
}

FGDALGeometryType UGDALFeatureDefinition::GetGeometryType() const
{
	return ConvToGDALGeometryType(FeatureDefinition->GetGeomType());
}
