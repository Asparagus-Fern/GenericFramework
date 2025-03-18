#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FDevEdCoreModule : public IModuleInterface
{
	/* IModuleInterface */
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
