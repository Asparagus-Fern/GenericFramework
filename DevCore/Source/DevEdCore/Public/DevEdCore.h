#pragma once

#include "CoreMinimal.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class FDevEdCoreModule : public ICommonEdModuleInterface
{
protected:
	virtual void PostStartupModule() override;
	virtual void LoadDependentModule(TArray<FName>& InDependentModuleName) override;
	virtual void RegisterStyle() override;
	virtual void RegisterAssetActions(TArray<TSharedPtr<FAssetTypeActions>>& OutAssetActions) override;
	virtual void UnRegisterStyle() override;
};
