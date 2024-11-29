// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDALType.h"
#include "UObject/Object.h"
#include "GDALLayer.generated.h"

class UGDALFeature;
class UGDALFeatureDefinition;
class UGDALGeometry;
class OGRLayer;

/**
 * OGRLayer For Unreal
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UGDALLayer : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(OGRLayer* InDataSource);
	virtual void Deinitialize();

	OGRLayer* GetDataSource() const { return DataSource; }

public:
	/* Return the layer name. */
	UFUNCTION(BlueprintPure)
	FString GetLayerName() const;

	/* Return the layer geometry type. */
	UFUNCTION(BlueprintPure)
	FGDALGeometryType GetGeometryType() const;

	/* Fetch the feature count in this layer. */
	UFUNCTION(BlueprintPure)
	int32 GetFeatureCount() const;

	/* Fetch a feature by its identifier. */
	UFUNCTION(BlueprintCallable)
	UGDALFeature* GetFeature(int64 ID);

public:
	UFUNCTION(BlueprintPure)
	UGDALFeatureDefinition* GetFeatureDefinition() const { return FeatureDefinition; }

	UFUNCTION(BlueprintPure)
	TArray<UGDALFeature*> GetFeatures() const { return Features; }

private:
	OGRLayer* DataSource = nullptr;

	UPROPERTY()
	UGDALFeatureDefinition* FeatureDefinition;

	UPROPERTY()
	TArray<UGDALFeature*> Features;
};
