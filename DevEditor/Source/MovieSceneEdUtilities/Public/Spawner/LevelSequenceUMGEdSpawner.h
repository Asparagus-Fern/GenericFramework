// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceUMGSpawner.h"

/**
 * 
 */
class MOVIESCENEUMGEDMODULE_API FLevelSequenceUMGEdSpawner : public FLevelSequenceUMGSpawner
{
public:
	static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();

	virtual bool IsEditor() const override { return true; }
#if WITH_EDITOR
	virtual TValueOrError<FNewSpawnable, FText> CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory = nullptr) override;
	virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;
	virtual bool CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const override;
#endif	
};
