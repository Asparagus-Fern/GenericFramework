#include "BuildingsInteractionEdSystem.h"

#define LOCTEXT_NAMESPACE "FBuildingsInteractionEdSystemModule"

void FBuildingsInteractionEdSystemModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();
}

void FBuildingsInteractionEdSystemModule::ShutdownModule()
{
	ICommonEdModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBuildingsInteractionEdSystemModule, BuildingsInteractionEdSystem)
