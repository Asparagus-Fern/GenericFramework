// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/CommonObject.h"

#include "Manager/ManagerSubsystem.h"

UWorld* UCommonObject::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("CommonButtonEvent: %s has a null OuterPrivate in UCommonButtonEvent::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return UManagerSubsystem::Get()->GetWorld();
	}
	return nullptr;
}
