#pragma once

#include "CoreMinimal.h"

class FWorldWidgetGenerationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
