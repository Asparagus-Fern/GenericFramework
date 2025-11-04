// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Asset/GenericAssetFactory.h"

bool UGenericAssetFactory::CanCreateNew() const
{
	return true;
}

UObject* UGenericAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return Super::FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn);
}
