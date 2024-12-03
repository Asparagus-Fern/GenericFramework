// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ogr_core.h"
#include "UObject/Object.h"
#include "GDALFeature.generated.h"

class UGDALGeometry;
class OGRFieldDefn;
class OGRFeature;

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UGDALFeature : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(OGRFeature* InDataSource);
	virtual void Deinitialize();

	OGRFeature* GetDataSource() const { return DataSource; }

public:
	UFUNCTION(BlueprintPure)
	int64 GetFeatureID() const;
	
	UFUNCTION(BlueprintPure)
	int32 GetFieldCount() const;

	UFUNCTION(BlueprintPure)
	FString GetFieldNameByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	int32 GetFieldIndexByName(FString FieldName) const;

public:
	UFUNCTION(BlueprintPure)
	int32 GetFieldAsIntegerByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	int32 GetFieldAsIntegerByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	TArray<int32> GetFieldAsIntegerArrayByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	TArray<int32> GetFieldAsIntegerArrayByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	int64 GetFieldAsInteger64ByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	int64 GetFieldAsInteger64ByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	TArray<int64> GetFieldAsInteger64ArrayByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	TArray<int64> GetFieldAsInteger64ArrayByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	double GetFieldAsDoubleByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	double GetFieldAsDoubleByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	TArray<double> GetFieldAsDoubleArrayByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	TArray<double> GetFieldAsDoubleArrayByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	FString GetFieldAsStringByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	FString GetFieldAsStringByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	TArray<FString> GetFieldAsStringArrayByIndex(int32 FieldIndex) const;

	UFUNCTION(BlueprintPure)
	TArray<FString> GetFieldAsStringArrayByName(FString FieldName) const;

	UFUNCTION(BlueprintPure)
	FDateTime GetFieldAsDataTimeByIndex(int32 FieldIndex) const;

public:
	/* Fetch pointer to feature geometry. */
	UFUNCTION(BlueprintPure)
	UGDALGeometry* GetGeometry() const { return Geometry; }

private:
	OGRFeature* DataSource = nullptr;

	UPROPERTY()
	UGDALGeometry* Geometry = nullptr;
};
