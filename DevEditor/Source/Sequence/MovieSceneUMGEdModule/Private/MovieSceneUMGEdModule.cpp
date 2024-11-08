#include "MovieSceneUMGEdModule.h"

#include "ISequencerModule.h"
#include "MovieSceneUMGTrackEditor.h"

#define LOCTEXT_NAMESPACE "FMovieSceneUMGEdModuleModule"

void FMovieSceneUMGEdModuleModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	UMGTrackCreateEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FMovieSceneUMGTrackEditor::CreateTrackEditor));
}

void FMovieSceneUMGEdModuleModule::ShutdownModule()
{
	ICommonEdModuleInterface::ShutdownModule();

	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(UMGTrackCreateEditorHandle);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMovieSceneUMGEdModuleModule, MovieSceneUMGEdModule)
