// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDALDate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GDAL.generated.h"

class UGDALFeature;
class UGDALDate;

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALGDAL_API UBPFunctions_GDAL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InClass"))
	static UGDALDate* LoadGDALData(FString InPath, TSubclassOf<UGDALDate> InClass);

	UFUNCTION(BlueprintPure)
	static FVector ConvGeoCoordinateToEngineLocation(AGeoReferencingSystem* GeoReferencingSystem, FVector InCoordinate);

	/* Test */
public:
	UFUNCTION(BlueprintCallable, CustomThunk, BlueprintInternalUseOnly, Category="GDAL", meta = (CustomStructureParam = "OutValue", AutoCreateRefTerm = "OutValue"))
	static UPARAM(DisplayName="Success") bool GetGDALField(UGDALFeature* Layer, const FString& FieldName, UPARAM(DisplayName="Value") int32& OutValue);
	DECLARE_FUNCTION(execGetGDALField);

private:
	static bool GDALFieldToProperty(UGDALFeature* InFeature, const FString& InFieldName, const FProperty* TargetProperty, void* TargetValuePtr);
};
