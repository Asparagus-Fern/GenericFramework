// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "Manager/CoreInternalManager.h"
#include "SceneManager.generated.h"

class AMapScaleActor;
class ACompassActor;

/**
 * 
 */
UCLASS()
class WORLDUTILITIES_API USceneManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FCoreInternalManager */
public:
	virtual void OnWorldMatchStarting(UWorld* InWorld) override;
	virtual void OnWorldEndPlay(UWorld* InWorld) override;

	/* USceneManager */
public:
	TArray<AActor*> FindActors(const FFindActorHandle& InFindActorHandle, bool bUpdate);
	TArray<AActor*> FindActors(const FFindActorHandle& InFindActorHandle) const;

	/* Compass */
public:
	float GetPlayerPointToNorthAngle(int32 PlayerIndex) const;

	/* MapScale */
public:
	float GetWorldElevationOriginHeight() const;

protected:
	UPROPERTY(Transient)
	TArray<FFoundActorHandle> FoundActorHandles;

	UPROPERTY(Transient)
	ACompassActor* CompassActor = nullptr;

	UPROPERTY(Transient)
	AMapScaleActor* MapScaleActor = nullptr;
};
