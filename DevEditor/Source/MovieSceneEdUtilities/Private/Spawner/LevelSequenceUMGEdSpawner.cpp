// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceUMGEdSpawner.h"

#include "MovieScene.h"
#include "Blueprint/UserWidgetBlueprint.h"

TSharedRef<IMovieSceneObjectSpawner> FLevelSequenceUMGEdSpawner::CreateObjectSpawner()
{
	return MakeShareable(new FLevelSequenceUMGEdSpawner);
}

TValueOrError<FNewSpawnable, FText> FLevelSequenceUMGEdSpawner::CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory)
{
	FNewSpawnable NewSpawnable(nullptr, FName::NameToDisplayString(SourceObject.GetName(), false));

	if (UUserWidgetBlueprint* UserWidgetBlueprint = Cast<UUserWidgetBlueprint>(&SourceObject))
	{
		// NewSpawnable.ObjectTemplate = UserWidgetBlueprint;
		NewSpawnable.ObjectTemplate = NewObject<UObject>(&OwnerMovieScene, UserWidgetBlueprint->GeneratedClass);
	}
	
	return MakeValue(NewSpawnable);
}

void FLevelSequenceUMGEdSpawner::SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings)
{
	FLevelSequenceUMGSpawner::SetupDefaultsForSpawnable(SpawnedObject, Guid, TransformData, Sequencer, Settings);
}

bool FLevelSequenceUMGEdSpawner::CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const
{
	return FLevelSequenceUMGSpawner::CanSetupDefaultsForSpawnable(SpawnedObject);
}
