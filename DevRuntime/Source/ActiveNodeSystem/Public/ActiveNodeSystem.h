#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FActiveNodeSystemModule : public ICommonModuleInterface
{
public:
	virtual void GetRegisterManager(TArray<TSubclassOf<UCoreManager>>& InRegisterManagerClasses) override;
};
