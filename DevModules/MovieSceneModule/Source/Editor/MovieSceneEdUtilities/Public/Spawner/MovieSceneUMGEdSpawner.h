// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Spawner/MovieSceneUMGSpawner.h"

/**
 * 
 */
class FMovieSceneUMGEdSpawner : public FMovieSceneUMGSpawner
{
public:
	static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();

	virtual bool IsEditor() const override { return true; }
#if WITH_EDITOR
	virtual TValueOrError<FNewSpawnable, FText> CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory = nullptr) override;
	virtual bool CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const override;
	virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;
#endif
};
