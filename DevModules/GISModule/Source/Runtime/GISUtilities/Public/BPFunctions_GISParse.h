// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GISParse.generated.h"

class GDALDataset;
class AGeoReferencingSystem;

USTRUCT(BlueprintType)
struct FLineCoordinate
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPointCoordinate = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPointCoordinate = FVector::ZeroVector;
};

/**
 * 
 */
UCLASS()
class GISUTILITIES_API UBPFunctions_GISParse : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* SHP */
public:
	static GDALDataset* LoadSHPDate(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath);

	UFUNCTION(BlueprintCallable)
	static bool ParseSHPAsPoint(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath, TArray<FVector>& PointCoordinates);

	UFUNCTION(BlueprintCallable)
	static bool ParseSHPAsLine(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath, TArray<FLineCoordinate>& LineCoordinates);
};
