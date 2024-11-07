#include "SequenceUMGEdSystem.h"

#define LOCTEXT_NAMESPACE "FSequenceUMGEdSystemModule"

void FSequenceUMGEdSystemModule::StartupModule()
{
	ICommonEdModuleInterface::StartupModule();
}

void FSequenceUMGEdSystemModule::ShutdownModule()
{
	ICommonEdModuleInterface::ShutdownModule();
}

void FSequenceUMGEdSystemModule::LoadDependentModule(TArray<FName>& InDependentModuleName)
{
	ICommonEdModuleInterface::LoadDependentModule(InDependentModuleName);
	InDependentModuleName.Add("SequenceUMGSystem");
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSequenceUMGEdSystemModule, SequenceUMGEdSystem)