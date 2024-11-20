#include "GISUtilities.h"

#define LOCTEXT_NAMESPACE "FGISUtilitiesModule"

void FGISUtilitiesModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FGISUtilitiesModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGISUtilitiesModule, GISUtilities)
