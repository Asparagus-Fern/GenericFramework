#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class FBuildingsInteractionEdSystemModule : public ICommonEdModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
