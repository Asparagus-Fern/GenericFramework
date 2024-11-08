#include "MovieSceneUMGModule.h"

#define LOCTEXT_NAMESPACE "FMovieSceneUMGModuleModule"

void FMovieSceneUMGModuleModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FMovieSceneUMGModuleModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMovieSceneUMGModuleModule, MovieSceneUMGModule)