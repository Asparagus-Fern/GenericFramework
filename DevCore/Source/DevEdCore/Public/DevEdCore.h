#pragma once

#include "CoreMinimal.h"
#include "ISettingsViewer.h"
#include "Factory/AssetTypeActions.h"
#include "Modules/ModuleManager.h"

class ISettingsModule;
class ISettingsEditorModel;

static const FName DeveloperAssetCategoryName("Developer");
static const FName DeveloperSettingsTabName("DeveloperSettings");

class FDevEdCoreModule : public IModuleInterface, public ISettingsViewer
{
	/* IModuleInterface */
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/* ISettingsViewer */
public:
	virtual void ShowSettings(const FName& CategoryName, const FName& SectionName) override;

protected:
	TWeakPtr<ISettingsEditorModel> SettingsEditorModelPtr;
	void RegisterManagerSettings(ISettingsModule& SettingsModule);
	void UnRegisterManagerSettings(ISettingsModule& SettingsModule);
	TSharedRef<SDockTab> HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs);

	/* ICommonEdModuleInterface */
protected:
	virtual void RegisterCommand();
	virtual void UnRegisterCommand();
};
