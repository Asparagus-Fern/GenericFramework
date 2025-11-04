// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GenericAssetFactory.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	DEVEDCORE_API virtual bool CanCreateNew() const override;
	DEVEDCORE_API virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
