#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "NiagaraComponent.h"
#include "Modules/ModuleManager.h"

class FApplicationEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
