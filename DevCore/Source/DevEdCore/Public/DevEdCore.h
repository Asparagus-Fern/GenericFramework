#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class FDevEdCoreModule : public ICommonEdModuleInterface
{
public:
	virtual void StartupModule() override;

protected:
	virtual void RegisterAssetActions(TArray<TSharedPtr<FAssetTypeActions>>& OutAssetActions) override;
};
