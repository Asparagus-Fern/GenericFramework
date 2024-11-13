#include "MovieSceneEdUtilities.h"

#include "ILevelSequenceModule.h"
#include "ISequencerModule.h"
#include "Spawner/MovieSceneUMGEdSpawner.h"
#include "TrackEditor/MovieSceneUMGTrackEditor.h"

#define LOCTEXT_NAMESPACE "FMovieSceneEdUtilitiesModule"

void FMovieSceneEdUtilitiesModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();

	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	EditorUMGSpawnerDelegateHandle = LevelSequenceModule.RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner::CreateStatic(&FMovieSceneUMGEdSpawner::CreateObjectSpawner));

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	UMGTrackCreateEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FMovieSceneUMGTrackEditor::CreateTrackEditor));
}

void FMovieSceneEdUtilitiesModule::ShutdownModule()
{
	ICommonEdModuleInterface::ShutdownModule();

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(UMGTrackCreateEditorHandle);

	ILevelSequenceModule* LevelSequenceModule = FModuleManager::GetModulePtr<ILevelSequenceModule>("LevelSequence");
	LevelSequenceModule->UnregisterObjectSpawner(EditorUMGSpawnerDelegateHandle);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMovieSceneEdUtilitiesModule, MovieSceneEdUtilities)
