#include "CharacterStateSystem.h"

#define LOCTEXT_NAMESPACE "FCharacterStateSystemModule"

void FCharacterStateSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FCharacterStateSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCharacterStateSystemModule, CharacterStateSystem)
