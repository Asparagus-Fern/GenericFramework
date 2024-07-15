#include "MapSystem.h"

#define LOCTEXT_NAMESPACE "FMapSystemModule"

void FMapSystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMapSystemModule, MapSystem)