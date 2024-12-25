// Fill out your copyright notice in the Description page of Project Settings.

#include "UltraDynamicSkySubsystem.h"

#include "UltraDynamicSkySettings.h"
#include "Kismet/GameplayStatics.h"

bool UUltraDynamicSkySubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UUltraDynamicSkySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// UGameplayStatics::GetActorOfClass(this)
}

void UUltraDynamicSkySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UUltraDynamicSkySubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UUltraDynamicSkySubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

TSubclassOf<AActor> UUltraDynamicSkySubsystem::GetUltraDynamicSkyClass()
{
	const TSoftClassPtr<AActor> UltraDynamicSkySoftClass = UUltraDynamicSkySettings::Get()->UltraDynamicSkyClass;
	if (UltraDynamicSkySoftClass.IsNull())
	{
		return nullptr;
	}

	TSubclassOf<AActor> UltraDynamicSkyClass;
	if (UltraDynamicSkySoftClass.IsPending())
	{
		UltraDynamicSkyClass = UltraDynamicSkySoftClass.LoadSynchronous();
	}
	else
	{
		UltraDynamicSkyClass = UltraDynamicSkySoftClass.Get();
	}

	return UltraDynamicSkyClass;
}

AActor* UUltraDynamicSkySubsystem::GetUltraDynamicSky()
{
	if (const TSubclassOf<AActor> UltraDynamicSkyClass = GetUltraDynamicSkyClass())
	{
		return UGameplayStatics::GetActorOfClass(this, UltraDynamicSkyClass);
	}

	return nullptr;
}
