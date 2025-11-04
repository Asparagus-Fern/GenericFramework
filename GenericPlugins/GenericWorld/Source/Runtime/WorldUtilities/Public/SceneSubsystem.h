// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "SceneSubsystem.generated.h"

class AMapScaleActor;
class ACompassActor;

/**
 * 
 */
UCLASS(MinimalAPI)
class USceneSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WORLDUTILITIES_API USceneSubsystem* Get(const UObject* WorldContextObject);
	WORLDUTILITIES_API virtual void OnWorldMatchStarting() override;
	WORLDUTILITIES_API virtual void OnWorldBeginTearDown(UWorld* InWorld) override;

	/* USceneManager */
public:
	WORLDUTILITIES_API TArray<AActor*> FindActors(const FFindActorHandle& InFindActorHandle, bool bUpdate);
	WORLDUTILITIES_API TArray<AActor*> FindActors(const FFindActorHandle& InFindActorHandle) const;

	/* Compass */
public:
	WORLDUTILITIES_API float GetPlayerPointToNorthAngle(int32 PlayerIndex) const;

	/* MapScale */
public:
	WORLDUTILITIES_API float GetWorldElevationOriginHeight() const;

protected:
	UPROPERTY(Transient)
	TArray<FFoundActorHandle> FoundActorHandles;

	UPROPERTY(Transient)
	ACompassActor* CompassActor = nullptr;

	UPROPERTY(Transient)
	AMapScaleActor* MapScaleActor = nullptr;
};
