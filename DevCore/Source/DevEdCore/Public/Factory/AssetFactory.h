// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClassViewerFilter.h"
#include "Factories/Factory.h"
#include "AssetFactory.generated.h"

/**
 * 
 */
class FAssetFilter : public IClassViewerFilter
{
public:
	TSet<const UClass*> AllowedChildrenOfClasses;
	EClassFlags DisallowedClassFlags;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

/**
 * 
 */
UCLASS(Abstract)
class DEVEDCORE_API UAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UAssetFactory();
	virtual FText GetDisplayName() const override;
	virtual bool ConfigureProperties() override;

protected:
	FText AssetName;
	uint8 bPickClass : 1;
	UClass* PickClass;

protected:
	virtual void ConfigureClassViewerOptions(FClassViewerInitializationOptions& Options);
	virtual void ConfigureFilter(TSharedRef<FAssetFilter>& Filter);
};
