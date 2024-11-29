#include "UMGUtilities.h"

#define LOCTEXT_NAMESPACE "FUMGUtilitiesModule"

void FUMGUtilitiesModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FUMGUtilitiesModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FUMGUtilitiesModule, UMGUtilities)