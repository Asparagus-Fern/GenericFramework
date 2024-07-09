#include "MediaPlaySystem.h"

#include "MediaPlayManager.h"

#define LOCTEXT_NAMESPACE "FMediaPlaySystemModule"

void FMediaPlaySystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
	InRegisterManagerClasses.Add(UMediaPlayManager::StaticClass());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMediaPlaySystemModule, MediaPlaySystem)
