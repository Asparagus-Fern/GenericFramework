#pragma once

#include "CoreMinimal.h"
#include "Module/CommonModuleInterface.h"
/**
 * 
 */
class FScreenWidgetGenerationModule : public ICommonModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
