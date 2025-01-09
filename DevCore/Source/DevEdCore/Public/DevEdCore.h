#pragma once

#include "CoreMinimal.h"
#include "ISettingsViewer.h"
#include "Modules/ModuleManager.h"

class ISettingsModule;
class ISettingsEditorModel;

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

	/* FDevEdCoreModule */
protected:
	TWeakPtr<ISettingsEditorModel> SettingsEditorModelPtr;
	void RegisterManagerSettings(ISettingsModule& SettingsModule);
	void UnRegisterManagerSettings(ISettingsModule& SettingsModule);
	TSharedRef<SDockTab> HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs);

protected:
	virtual void RegisterCommand();
	virtual void UnRegisterCommand();
};
