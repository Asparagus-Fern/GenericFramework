// Copyright ChenTaiye 2025. All Rights Reserved.

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
	virtual uint32 GetMenuCategories() const override;
};
