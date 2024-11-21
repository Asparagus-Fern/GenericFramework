// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GISParse.generated.h"

class AGeoReferencingSystem;

USTRUCT(BlueprintType)
struct FLineCoordinate
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartPointCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPointCoordinate;
};

/**
 * 
 */
UCLASS()
class GISUTILITIES_API UBPFunctions_GISParse : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

/*public:
	UFUNCTION(BlueprintCallable)
	static bool ParseSHPAsPoint(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath, TArray<FVector>& PointCoordinates);

	UFUNCTION(BlueprintCallable)
	static bool ParseSHPAsLine(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath, TArray<FLineCoordinate>& LineCoordinates);*/
};
