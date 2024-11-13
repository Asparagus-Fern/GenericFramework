#include "BuildingsInteractionSystem.h"

#define LOCTEXT_NAMESPACE "FBuildingsInteractionSystemModule"

void FBuildingsInteractionSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FBuildingsInteractionSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBuildingsInteractionSystemModule, BuildingsInteractionSystem)
