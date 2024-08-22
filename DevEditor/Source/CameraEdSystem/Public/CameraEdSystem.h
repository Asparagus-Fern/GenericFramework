#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class FCameraEdSystemModule : public ICommonEdModuleInterface
{
protected:
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
