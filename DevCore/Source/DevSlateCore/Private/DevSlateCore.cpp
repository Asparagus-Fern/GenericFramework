#include "DevSlateCore.h"

#include "DevCoreStyle.h"

#define LOCTEXT_NAMESPACE "FDevSlateCoreModule"

void FDevSlateCoreModule::StartupModule()
{
	FDevCoreStyle::Initialize();
}

void FDevSlateCoreModule::ShutdownModule()
{
	FDevCoreStyle::ShoutDown();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FDevSlateCoreModule, DevSlateCore)