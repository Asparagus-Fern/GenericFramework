// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GDALSpatialReference.generated.h"

class OGRSpatialReference;

/**
 * 
 */
UCLASS()
class UNREALGDAL_API UGDALSpatialReference : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(const OGRSpatialReference* InDataSource);
	virtual void Deinitialize();

	const OGRSpatialReference* GetDataSource() const { return DataSource; }

private:
	const OGRSpatialReference* DataSource = nullptr;
};
