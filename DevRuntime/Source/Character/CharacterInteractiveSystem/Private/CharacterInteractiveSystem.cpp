#include "CharacterInteractiveSystem.h"

#define LOCTEXT_NAMESPACE "FCharacterInteractiveSystemModule"

void FCharacterInteractiveSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FCharacterInteractiveSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCharacterInteractiveSystemModule, CharacterInteractiveSystem)