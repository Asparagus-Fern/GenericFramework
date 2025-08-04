// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Spawner/MovieSceneUMGEdSpawner.h"

#include "MovieScene.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "ISequencer.h"
#include "Blueprint/UserWidget.h"
#include "Sections/MovieSceneBoolSection.h"
#include "Tracks/MovieSceneSpawnTrack.h"

#define LOCTEXT_NAMESPACE "FMovieSceneEdUtilitiesModule"

TSharedRef<IMovieSceneObjectSpawner> FMovieSceneUMGEdSpawner::CreateObjectSpawner()
{
    return MakeShareable(new FMovieSceneUMGEdSpawner);
}

#if WITH_EDITOR

TValueOrError<FNewSpawnable, FText> FMovieSceneUMGEdSpawner::CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory)
{
	FNewSpawnable NewSpawnable(nullptr, FName::NameToDisplayString(SourceObject.GetName(), false));

	/* 提供实例供Sequencer修改并序列化保存 */
	if (const UUserWidgetBlueprint* UserWidgetBlueprint = Cast<UUserWidgetBlueprint>(&SourceObject))
	{
		NewSpawnable.ObjectTemplate = NewObject<UObject>(&OwnerMovieScene, UserWidgetBlueprint->GeneratedClass);
	}

	/* 非UMG类生成时，标记该Spawnable为无效 */
	if (!NewSpawnable.ObjectTemplate || !NewSpawnable.ObjectTemplate->IsA<UUserWidget>())
	{
		return MakeError(FText::Format(LOCTEXT("UnknownClassError", "Unable to create a new spawnable object from {0}."), FText::FromString(SourceObject.GetName())));
	}

	return MakeValue(NewSpawnable);
}

bool FMovieSceneUMGEdSpawner::CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const
{
	if (SpawnedObject == nullptr)
	{
		return true;
	}
	
	return FMovieSceneUMGSpawner::CanSetupDefaultsForSpawnable(SpawnedObject);
}

void FMovieSceneUMGEdSpawner::SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings)
{
	UMovieSceneSequence* Sequence = Sequencer->GetFocusedMovieSceneSequence();
	UMovieScene* OwnerMovieScene = Sequence->GetMovieScene();

	/* 添加默认的SpawnTrack */
	UMovieSceneSpawnTrack* SpawnTrack = Cast<UMovieSceneSpawnTrack>(OwnerMovieScene->FindTrack(UMovieSceneSpawnTrack::StaticClass(), Guid, NAME_None));
	if (!SpawnTrack)
	{
		SpawnTrack = Cast<UMovieSceneSpawnTrack>(OwnerMovieScene->AddTrack(UMovieSceneSpawnTrack::StaticClass(), Guid));
	}

	if (SpawnTrack)
	{
		UMovieSceneBoolSection* SpawnSection = Cast<UMovieSceneBoolSection>(SpawnTrack->CreateNewSection());
		SpawnSection->GetChannel().SetDefault(true);
		if (Sequencer->GetInfiniteKeyAreas())
		{
			SpawnSection->SetRange(TRange<FFrameNumber>::All());
		}
		SpawnTrack->AddSection(*SpawnSection);
		SpawnTrack->SetObjectId(Guid);
	}
}

#endif

#undef LOCTEXT_NAMESPACE
