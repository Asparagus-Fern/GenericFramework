#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"

class FWorldWidgetGenerationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
