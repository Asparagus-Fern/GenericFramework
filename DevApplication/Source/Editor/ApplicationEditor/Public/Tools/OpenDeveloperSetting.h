// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "ISettingsViewer.h"
#include "OpenDeveloperSetting.generated.h"

class ISettingsModule;
class ISettingsEditorModel;

static const FName GenericFrameworkSettingsTabName("GenericFrameworkSettings");

/**
 * 
 */
UCLASS()
class APPLICATIONEDITOR_API UOpenDeveloperSetting : public UEditorSubsystem, public ISettingsViewer
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* ISettingsViewer */
public:
	virtual void ShowSettings(const FName& CategoryName, const FName& SectionName) override;

protected:
	TWeakPtr<ISettingsEditorModel> SettingsEditorModelPtr;
	TSharedRef<SDockTab> HandleSpawnSettingsTab(const FSpawnTabArgs& SpawnTabArgs);

private:
	virtual void RegisterToolBarGenericFrameworkSetting(FToolMenuSection& ToolMenuSection);
	virtual void OpenToolBarGenericFrameworkSetting();
};
