#include "SequenceUMGSystem.h"

#define LOCTEXT_NAMESPACE "FSequenceUMGSystemModule"

void FSequenceUMGSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FSequenceUMGSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSequenceUMGSystemModule, SequenceUMGSystem)
