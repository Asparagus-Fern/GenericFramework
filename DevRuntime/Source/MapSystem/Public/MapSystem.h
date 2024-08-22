#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
#include "Modules/ModuleManager.h"

class FMapSystemModule : public ICommonModuleInterface
{
public:
	virtual void StartupModule() override;
};
