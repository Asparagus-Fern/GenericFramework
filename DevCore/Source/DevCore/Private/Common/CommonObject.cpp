// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Common/CommonObject.h"

#include "Debug/DebugType.h"

UCommonObject::UCommonObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UWorld* UCommonObject::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("CommonObject: %s has a null OuterPrivate in UCommonObject::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}