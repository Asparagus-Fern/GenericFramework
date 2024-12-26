// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Public/Subsystems/WorldSubsystem.h"
#include "UltraDynamicSkySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ULTRADYNAMICSKYUTILITIES_API UUltraDynamicSkySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

public:
	static TSubclassOf<AActor> GetUltraDynamicSkyClass();
	AActor* GetUltraDynamicSky();
};
