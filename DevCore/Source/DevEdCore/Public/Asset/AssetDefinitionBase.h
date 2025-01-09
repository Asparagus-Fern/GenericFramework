// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "AssetDefinitionBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEVEDCORE_API UAssetDefinitionBase : public UAssetDefinitionDefault
{
	GENERATED_BODY()

public:
	virtual FLinearColor GetAssetColor() const override { return FLinearColor(FColor(201, 29, 85)); }
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;

private:
	static FAssetCategoryPath DeveloperCategory;
};
