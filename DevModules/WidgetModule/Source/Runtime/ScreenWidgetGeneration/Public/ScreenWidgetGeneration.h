#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FScreenWidgetGenerationModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
