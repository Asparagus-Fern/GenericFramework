#include "LevelStreaming.h"

#include "LevelStreamingManager.h"

#define LOCTEXT_NAMESPACE "FLevelStreamingModule"

void FLevelStreamingModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FLevelStreamingModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLevelStreamingModule, LevelStreaming)
