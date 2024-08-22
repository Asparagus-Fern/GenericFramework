#include "MapSystem.h"

#define LOCTEXT_NAMESPACE "FMapSystemModule"

void FMapSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMapSystemModule, MapSystem)
