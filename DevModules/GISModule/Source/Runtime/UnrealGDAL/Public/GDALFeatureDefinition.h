// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDALType.h"
#include "UObject/Object.h"
#include "GDALFeatureDefinition.generated.h"

class OGRFieldDefn;
class OGRFeatureDefn;

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UGDALFeatureDefinition : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(OGRFeatureDefn* InDataSource);
	virtual void Deinitialize();

public:
	/* Get name of this OGRFeatureDefn. */
	UFUNCTION(BlueprintPure)
	FString GetDefinitionName() const;

	/* Change name of this OGRFeatureDefn. */
	UFUNCTION(BlueprintCallable)
	void SetDefinitionName(FString InName);

	/* Fetch number of fields on this feature. */
	UFUNCTION(BlueprintPure)
	int32 GetFieldCount() const;

	/* Fetch name of this field. */
	UFUNCTION(BlueprintPure)
	FString GetFieldName(int32 Index);

	/* Reset the name of this field. */
	UFUNCTION(BlueprintCallable)
	void SetFieldName(int32 Index, FString InName);

	/* Get default field value. */
	UFUNCTION(BlueprintPure)
	FString GetFieldDefault(int32 Index);

	/* Set default field value. */
	UFUNCTION(BlueprintCallable)
	void SetFieldDefault(int32 Index, FString InName);

	/* Find field by name. */
	UFUNCTION(BlueprintPure)
	int32 GetFieldIndex(FString InName) const;

	/* Return the layer geometry type. */
	UFUNCTION(BlueprintPure)
	FGDALGeometryType GetGeometryType() const;

public:
	OGRFeatureDefn* GetFeatureDefinition() const { return FeatureDefinition; }

private:
	OGRFeatureDefn* FeatureDefinition = nullptr;
	TArray<OGRFieldDefn*> Fields;
};
