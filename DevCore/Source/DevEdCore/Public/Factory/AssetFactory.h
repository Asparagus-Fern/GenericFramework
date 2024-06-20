// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetFactory.generated.h"

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

protected:
	FText AssetName;
};
