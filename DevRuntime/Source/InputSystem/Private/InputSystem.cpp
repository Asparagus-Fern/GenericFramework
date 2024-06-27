#include "InputSystem.h"

#define LOCTEXT_NAMESPACE "FInputSystemModule"

void FInputSystemModule::GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses)
{
	ICommonModuleInterface::GetRegisterManager(InRegisterManagerClasses);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInputSystemModule, InputSystem)
