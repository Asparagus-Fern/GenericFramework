// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GDALRasterBand.generated.h"

class GDALRasterBand;

/**
 * 
 */
UCLASS()
class UNREALGDAL_API UGDALRasterBand : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(GDALRasterBand* InDataSource);
	virtual void Deinitialize();

	GDALRasterBand* GetDataSource() const { return DataSource; }

private:
	GDALRasterBand* DataSource = nullptr;
};
