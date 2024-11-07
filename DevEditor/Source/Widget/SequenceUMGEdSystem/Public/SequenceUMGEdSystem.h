#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class FSequenceUMGEdSystemModule : public ICommonEdModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
