#include "WorldUtilities.h"

#define LOCTEXT_NAMESPACE "FWorldUtilitiesModule"

void FWorldUtilitiesModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FWorldUtilitiesModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWorldUtilitiesModule, WorldUtilities)
