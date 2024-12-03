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

int64 UGDALFeature::GetFeatureID() const
{
	return DataSource->GetFID();
}

int32 UGDALFeature::GetFieldCount() const
{
	return DataSource->GetFieldCount();
}

FString UGDALFeature::GetFieldNameByIndex(int32 FieldIndex) const
{
	return UTF8_TO_TCHAR(DataSource->GetFieldDefnRef(FieldIndex)->GetNameRef());
}

int32 UGDALFeature::GetFieldIndexByName(FString FieldName) const
{
	return DataSource->GetFieldIndex(TCHAR_TO_UTF8(*FieldName));
}

int32 UGDALFeature::GetFieldAsIntegerByIndex(int32 FieldIndex) const
{
	return DataSource->GetFieldAsInteger(FieldIndex);
}

int32 UGDALFeature::GetFieldAsIntegerByName(FString FieldName) const
{
	return DataSource->GetFieldAsInteger(TCHAR_TO_UTF8(*FieldName));
}

TArray<int32> UGDALFeature::GetFieldAsIntegerArrayByIndex(int32 FieldIndex) const
{
	TArray<int32> Value;

	int* Count = nullptr;
	const int* Array = DataSource->GetFieldAsIntegerList(FieldIndex, Count);

	for (auto It = 0; It < *Count; It++)
	{
		Value.Add(Array[It]);
	}

	return Value;
}

TArray<int32> UGDALFeature::GetFieldAsIntegerArrayByName(FString FieldName) const
{
	TArray<int32> Value;

	int* Count = nullptr;
	const int* Array = DataSource->GetFieldAsIntegerList(TCHAR_TO_UTF8(*FieldName), Count);

	for (auto It = 0; It < *Count; It++)
	{
		Value.Add(Array[It]);
	}

	return Value;
}

int64 UGDALFeature::GetFieldAsInteger64ByIndex(int32 FieldIndex) const
{
	return DataSource->GetFieldAsInteger64(FieldIndex);
}

int64 UGDALFeature::GetFieldAsInteger64ByName(FString FieldName) const
{
	return DataSource->GetFieldAsInteger64(TCHAR_TO_UTF8(*FieldName));
}

TArray<int64> UGDALFeature::GetFieldAsInteger64ArrayByIndex(int32 FieldIndex) const
{
	TArray<int64> Value;

	int* Count = nullptr;
	const GIntBig* Array = DataSource->GetFieldAsInteger64List(FieldIndex, Count);

	for (auto It = 0; It < *Count; It++)
	{
		Value.Add(Array[It]);
	}

	return Value;
}

TArray<int64> UGDALFeature::GetFieldAsInteger64ArrayByName(FString FieldName) const
{
	TArray<int64> Value;

	int* Count = nullptr;
	const GIntBig* Array = DataSource->GetFieldAsInteger64List(TCHAR_TO_UTF8(*FieldName), Count);

	for (auto It = 0; It < *Count; It++)
	{
		Value.Add(Array[It]);
	}

	return Value;
}

double UGDALFeature::GetFieldAsDoubleByIndex(int32 FieldIndex) const
{
	return DataSource->GetFieldAsDouble(FieldIndex);
}

double UGDALFeature::GetFieldAsDoubleByName(FString FieldName) const
{
	return DataSource->GetFieldAsDouble(TCHAR_TO_UTF8(*FieldName));
}

TArray<double> UGDALFeature::GetFieldAsDoubleArrayByIndex(int32 FieldIndex) const
{
	TArray<double> Value;

	int* Count = nullptr;
	const double* Array = DataSource->GetFieldAsDoubleList(FieldIndex, Count);

	for (auto It = 0; It < *Count; It++)
	{
		Value.Add(Array[It]);
	}

	return Value;
}

TArray<double> UGDALFeature::GetFieldAsDoubleArrayByName(FString FieldName) const
{
	TArray<double> Value;

	int* Count = nullptr;
	const double* Array = DataSource->GetFieldAsDoubleList(TCHAR_TO_UTF8(*FieldName), Count);

	for (auto It = 0; It < *Count; It++)
	{
		Value.Add(Array[It]);
	}

	return Value;
}

FString UGDALFeature::GetFieldAsStringByIndex(int32 FieldIndex) const
{
	return UTF8_TO_TCHAR(DataSource->GetFieldAsString(FieldIndex));
}

FString UGDALFeature::GetFieldAsStringByName(FString FieldName) const
{
	return UTF8_TO_TCHAR(DataSource->GetFieldAsString(TCHAR_TO_UTF8(*FieldName)));
}

TArray<FString> UGDALFeature::GetFieldAsStringArrayByIndex(int32 FieldIndex) const
{
	TArray<FString> Value;
	char** Array = DataSource->GetFieldAsStringList(FieldIndex);
	const int Count = CSLCount(Array);

	for (auto It = 0; It < Count; It++)
	{
		Value.Add(UTF8_TO_TCHAR(Array[It]));
	}

	return Value;
}

TArray<FString> UGDALFeature::GetFieldAsStringArrayByName(FString FieldName) const
{
	TArray<FString> Value;
	char** Array = DataSource->GetFieldAsStringList(TCHAR_TO_UTF8(*FieldName));
	const int Count = CSLCount(Array);

	for (auto It = 0; It < Count; It++)
	{
		Value.Add(UTF8_TO_TCHAR(Array[It]));
	}

	return Value;
}

FDateTime UGDALFeature::GetFieldAsDataTimeByIndex(int32 FieldIndex) const
{
	int* Year = nullptr;
	int* Month = nullptr;
	int* Day = nullptr;
	int* Hour = nullptr;
	int* Minute = nullptr;
	int* Second = nullptr;

	FDateTime Value;

	if (DataSource->GetFieldAsDateTime(FieldIndex, Year, Month, Day, Hour, Minute, Second, nullptr))
	{
		Value = FDateTime(*Year, *Month, *Day, *Hour, *Minute, *Second, 0);
	}

	return Value;
}
