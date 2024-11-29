// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	/* Fetch pointer to feature geometry. */
	UFUNCTION(BlueprintPure)
	UGDALGeometry* GetGeometry() const { return Geometry; }

private:
	TArray<OGRFieldDefn*> Fields;
	OGRFeature* DataSource = nullptr;

	UPROPERTY()
	UGDALGeometry* Geometry = nullptr;
};
