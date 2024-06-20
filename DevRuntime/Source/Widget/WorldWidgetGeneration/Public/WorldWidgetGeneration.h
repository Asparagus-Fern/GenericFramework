#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"

class FWorldWidgetGenerationModule : public ICommonModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
};
