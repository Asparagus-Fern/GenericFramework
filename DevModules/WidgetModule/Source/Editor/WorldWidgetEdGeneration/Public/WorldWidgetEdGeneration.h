#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"

class FWorldWidgetEdGenerationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
