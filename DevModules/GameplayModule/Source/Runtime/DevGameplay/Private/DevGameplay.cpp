#include "DevGameplay.h"

#define LOCTEXT_NAMESPACE "FDevGameplayModule"

void FDevGameplayModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FDevGameplayModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDevGameplayModule, DevGameplay)
