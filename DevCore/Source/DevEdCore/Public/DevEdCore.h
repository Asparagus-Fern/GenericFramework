#pragma once

#include "CoreMinimal.h"
#include "ISettingsViewer.h"
#include "Module/CommonEdModuleInterface.h"
#include "Modules/ModuleManager.h"

class ISettingsModule;
class ISettingsEditorModel;

class FDevEdCoreModule : public ICommonEdModuleInterface, public ISettingsViewer
{
	/* IModuleInterface */
public:
	virtual void StartupModule() override;

	/* ISettingsViewer */
public:
	virtual void ShowSettings(const FName& CategoryName, const FName& SectionName) override;

protected:
	TWeakPtr<ISettingsEditorModel> SettingsEditorModelPtr;
	void RegisterManagerSettings(ISettingsModule& SettingsModule);
	TSharedRef<SDockTab> HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs);

	/* ICommonEdModuleInterface */
protected:
	virtual void RegisterCommand() override;
	virtual void RegisterAssetActions(TArray<TSharedPtr<FAssetTypeActions>>& OutAssetActions) override;
	virtual void UnRegisterCommand() override;
};
