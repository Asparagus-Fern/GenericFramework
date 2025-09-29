#include "MovieSceneExtend.h"

#include "ILevelSequenceModule.h"
#include "Spawner/MovieSceneUMGEdSpawner.h"
#include "Spawner/MovieSceneUMGSpawner.h"

#if WITH_EDITOR
#include "ISequencerModule.h"
#include "Track/MovieSceneUMGEdTrack.h"
#endif

#define LOCTEXT_NAMESPACE "FMovieSceneExtendModule"

void FMovieSceneExtendModule::StartupModule()
{
	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	OnCreateMovieSceneUMGSpawnerDelegateHandle = LevelSequenceModule.RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner::CreateStatic(&FMovieSceneUMGSpawner::CreateObjectSpawner));

#if WITH_EDITOR
	EditorUMGSpawnerDelegateHandle = LevelSequenceModule.RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner::CreateStatic(&FMovieSceneUMGEdSpawner::CreateObjectSpawner));
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	UMGTrackCreateEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FMovieSceneUMGEdTrack::CreateTrackEditor));
#endif
}

void FMovieSceneExtendModule::ShutdownModule()
{
	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	LevelSequenceModule.UnregisterObjectSpawner(OnCreateMovieSceneUMGSpawnerDelegateHandle);

#if WITH_EDITOR
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(UMGTrackCreateEditorHandle);
	LevelSequenceModule.UnregisterObjectSpawner(EditorUMGSpawnerDelegateHandle);
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMovieSceneExtendModule, MovieSceneExtend)
