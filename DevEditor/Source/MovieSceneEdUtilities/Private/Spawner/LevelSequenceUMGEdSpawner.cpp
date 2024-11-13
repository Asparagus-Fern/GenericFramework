// Fill out your copyright notice in the Description page of Project Settings.

#include "MovieScene.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "Spawner/MovieSceneUMGEdSpawner.h"

TSharedRef<IMovieSceneObjectSpawner> FMovieSceneUMGEdSpawner::CreateObjectSpawner()
{
	return MakeShareable(new FMovieSceneUMGEdSpawner);
}

TValueOrError<FNewSpawnable, FText> FMovieSceneUMGEdSpawner::CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory)
{
	FNewSpawnable NewSpawnable(nullptr, FName::NameToDisplayString(SourceObject.GetName(), false));

	if (UUserWidgetBlueprint* UserWidgetBlueprint = Cast<UUserWidgetBlueprint>(&SourceObject))
	{
		// NewSpawnable.ObjectTemplate = UserWidgetBlueprint;
		NewSpawnable.ObjectTemplate = NewObject<UObject>(&OwnerMovieScene, UserWidgetBlueprint->GeneratedClass);
	}

	return MakeValue(NewSpawnable);
}

void FMovieSceneUMGEdSpawner::SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings)
{
	FMovieSceneUMGSpawner::SetupDefaultsForSpawnable(SpawnedObject, Guid, TransformData, Sequencer, Settings);
}

bool FMovieSceneUMGEdSpawner::CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const
{
	return FMovieSceneUMGSpawner::CanSetupDefaultsForSpawnable(SpawnedObject);
}
