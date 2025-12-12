#include "GenericMovieSceneSystem.h"

#include "ILevelSequenceModule.h"
#include "Spawner/MovieSceneUMGSpawner.h"

#define LOCTEXT_NAMESPACE "FGenericMovieSceneSystemModule"

void FGenericMovieSceneSystemModule::StartupModule()
{
	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	OnCreateMovieSceneUMGSpawnerDelegateHandle = LevelSequenceModule.RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner::CreateStatic(&FMovieSceneUMGSpawner::CreateObjectSpawner));
}

void FGenericMovieSceneSystemModule::ShutdownModule()
{
	ILevelSequenceModule& LevelSequenceModule = FModuleManager::LoadModuleChecked<ILevelSequenceModule>("LevelSequence");
	LevelSequenceModule.UnregisterObjectSpawner(OnCreateMovieSceneUMGSpawnerDelegateHandle);

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGenericMovieSceneSystemModule, GenericMovieSceneSystem)
