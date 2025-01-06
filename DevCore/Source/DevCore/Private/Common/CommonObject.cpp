// Fill out your copyright notice in the Description page of Project Settings.


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

void UCommonObject::BeginDestroy()
{
	// NativeDeInitialize();
	// OnDeInitialized();
	// DLOG(DLogObject, Log, TEXT("On DeInitialize : %s"), *GetName());

	UObject::BeginDestroy();
}

void UCommonObject::OnInitialized_Implementation()
{
}

void UCommonObject::NativeInitialize()
{
}

void UCommonObject::OnDeInitialized_Implementation()
{
}

void UCommonObject::NativeDeInitialize()
{
}
