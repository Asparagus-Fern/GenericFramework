// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GDALGeometry.generated.h"

class OGRGeometry;

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UGDALGeometry : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(OGRGeometry* InDataSource);
	virtual void Deinitialize();

	OGRGeometry* GetDataSource() const { return DataSource; }

private:
	OGRGeometry* DataSource = nullptr;
};
