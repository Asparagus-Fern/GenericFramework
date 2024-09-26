#include "PropertyDetailViewSystem.h"

#define LOCTEXT_NAMESPACE "FPropertyDetailViewSystemModule"

void FPropertyDetailViewSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FPropertyDetailViewSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPropertyDetailViewSystemModule, PropertyDetailViewSystem)
