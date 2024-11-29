// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "SHPManager.generated.h"

class GDALDataset;
class AGeoReferencingSystem;

USTRUCT()
struct FSHPReference
{
	GENERATED_BODY()

public:
	FSHPReference();
	// FSHPReference(AGeoReferencingSystem* InGeoReferencing, USHPHandle* InSHPHandles);

	bool operator==(const AGeoReferencingSystem* Other) const { return GeoReferencingSystem == Other; }
	bool operator==(FSHPReference Other) const { return GeoReferencingSystem == Other.GeoReferencingSystem; }
	bool operator!=(const AGeoReferencingSystem* Other) const { return !(*this == Other); }
	bool operator!=(FSHPReference Other) const { return !(*this == Other); }

public:
	UPROPERTY()
	AGeoReferencingSystem* GeoReferencingSystem = nullptr;

	// UPROPERTY()
	// USHPHandle* SHPHandle = nullptr;
};

/**
 * 
 */
UCLASS()
class GISUTILITIES_API USHPManager : public UEngineSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void Test(AGeoReferencingSystem* GeoReferencing);

public:
	GDALDataset* LoadSHPDateSource(AGeoReferencingSystem* GeoReferencingSystem, const FString& SHPPath);
	// bool LoadSHP(AGeoReferencingSystem* GeoReferencingSystem, TArray<USHPHandle*>& OutSHPHandles);
	// static USHPHandle* MakeSHPHandle(AGeoReferencingSystem* GeoReferencingSystem, GDALDataset* DataSource);

protected:
	UPROPERTY()
	TArray<FSHPReference> SHPReferences;
};
