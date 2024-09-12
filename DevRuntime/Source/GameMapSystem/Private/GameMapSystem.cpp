#include "GameMapSystem.h"

#define LOCTEXT_NAMESPACE "FGameMapSystemModule"

void FGameMapSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FGameMapSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameMapSystemModule, GameMapSystem)
