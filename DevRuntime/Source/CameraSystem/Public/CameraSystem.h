#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FCameraSystemModule : public ICommonModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
