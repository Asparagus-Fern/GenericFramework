#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FDevGameplayModule : public ICommonModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
