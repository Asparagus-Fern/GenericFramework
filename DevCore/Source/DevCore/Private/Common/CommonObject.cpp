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

void UCommonObject::PostLoad()
{
	UObject::PostLoad();
	Initialize();
}

void UCommonObject::BeginDestroy()
{
	DeInitialize();
	UObject::BeginDestroy();
}

void UCommonObject::Initialize()
{
	DLOG(DLogObject, Log, TEXT("On Initialized : %s"), *GetName());
}

void UCommonObject::DeInitialize()
{
	DLOG(DLogObject, Log, TEXT("On DeInitialized : %s"), *GetName());
}
