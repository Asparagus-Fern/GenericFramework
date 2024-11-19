#include "MovieSceneUtilities.h"

#include "ILevelSequenceModule.h"
#include "Spawner/MovieSceneUMGSpawner.h"

#define LOCTEXT_NAMESPACE "FMovieSceneUtilitiesModule"

void FMovieSceneUtilitiesModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();

	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	OnCreateMovieSceneUMGSpawnerDelegateHandle = LevelSequenceModule.RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner::CreateStatic(&FMovieSceneUMGSpawner::CreateObjectSpawner));
}

void FMovieSceneUtilitiesModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();

	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	LevelSequenceModule.UnregisterObjectSpawner(OnCreateMovieSceneUMGSpawnerDelegateHandle);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMovieSceneUtilitiesModule, MovieSceneUtilities)
