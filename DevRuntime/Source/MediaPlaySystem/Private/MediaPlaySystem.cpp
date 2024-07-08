#include "MediaPlaySystem.h"

#define LOCTEXT_NAMESPACE "FMediaPlaySystemModule"

void FMediaPlaySystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMediaPlaySystemModule, MediaPlaySystem)