#include "MapEdSystem.h"

#define LOCTEXT_NAMESPACE "FMapEdSystemModule"

void FMapEdSystemModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMapEdSystemModule, MapEdSystem)
