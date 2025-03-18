#include "DevEdCore.h"

#define LOCTEXT_NAMESPACE "FDevEdCoreModule"

void FDevEdCoreModule::StartupModule()
{
	IModuleInterface::StartupModule();
}

void FDevEdCoreModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevEdCoreModule, DevEdCore)
