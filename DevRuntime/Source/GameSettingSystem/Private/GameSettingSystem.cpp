#include "GameSettingSystem.h"

#define LOCTEXT_NAMESPACE "FGameSettingSystemModule"

void FGameSettingSystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

void FGameSettingSystemModule::ShutdownModule()
{
	ICommonModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameSettingSystemModule, GameSettingSystem)
