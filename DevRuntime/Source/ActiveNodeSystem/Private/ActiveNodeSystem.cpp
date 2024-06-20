#include "ActiveNodeSystem.h"

#include "ActiveNodeManager.h"

#define LOCTEXT_NAMESPACE "FActiveNodeSystemModule"

void FActiveNodeSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FActiveNodeSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FActiveNodeSystemModule, ActiveNodeSystem)
