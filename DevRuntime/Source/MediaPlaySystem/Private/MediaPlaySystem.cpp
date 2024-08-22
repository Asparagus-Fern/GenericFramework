#include "MediaPlaySystem.h"

#include "MediaPlayManager.h"

#define LOCTEXT_NAMESPACE "FMediaPlaySystemModule"

void FMediaPlaySystemModule::StartupModule()
{
	ICommonModuleInterface::StartupModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMediaPlaySystemModule, MediaPlaySystem)
