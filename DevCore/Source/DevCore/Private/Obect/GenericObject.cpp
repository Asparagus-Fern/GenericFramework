// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Obect/GenericObject.h"

UGenericObject::UGenericObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UWorld* UGenericObject::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("GenericObject: %s has a null OuterPrivate in GenericObject::GetWorld()"), *GetFullName()) && !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}
