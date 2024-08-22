#include "ActiveNodeSystem.h"

#define LOCTEXT_NAMESPACE "FActiveNodeSystemModule"

void FActiveNodeSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FActiveNodeSystemModule, ActiveNodeSystem)
