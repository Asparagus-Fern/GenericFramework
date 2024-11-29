#include "BackpackSystem.h"

#define LOCTEXT_NAMESPACE "FBackpackSystemModule"

void FBackpackSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FBackpackSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBackpackSystemModule, BackpackSystem)
