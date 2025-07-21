// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SceneType.h"
#include "Interface/ManagerInterface.h"
#include "SceneManager.generated.h"

class AMapScaleActor;
class ACompassActor;

/**
 * 
 */
UCLASS(MinimalAPI)
class USceneManager : public UWorldSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* FCoreInternalManager */
public:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

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
