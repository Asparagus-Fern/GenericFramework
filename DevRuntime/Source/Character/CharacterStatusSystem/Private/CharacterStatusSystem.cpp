#include "CharacterStatusSystem.h"

#define LOCTEXT_NAMESPACE "FCharacterStatusSystemModule"

void FCharacterStatusSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FCharacterStatusSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCharacterStatusSystemModule, CharacterStatusSystem)
