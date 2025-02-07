#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "Modules/ModuleManager.h"

class FMenuGenerationEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
