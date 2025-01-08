#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "Modules/ModuleManager.h"

const FName MenuCollectionHierarchyTabID = " MenuCollectionHierarchy";

class FMenuGenerationEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterBlueprintEditorTab(FWorkflowAllowedTabSet& TabFactories, FName InModeName, TSharedPtr<FBlueprintEditor> BlueprintEditor);
	void RegisterBlueprintEditorLayout(FLayoutExtender& Extender);
	void OnAssetEditorOpened(UObject* InObject);
	
	FDelegateHandle BlueprintEditorTabSpawnerHandle, BlueprintEditorLayoutExtensionHandle, AssetEditorOpenedHandle;
};

struct FMenuCollectionEditorSummoner : public FWorkflowTabFactory
{
	FMenuCollectionEditorSummoner(TSharedPtr<FBlueprintEditor> BlueprintEditor);
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<FBlueprintEditor> WeakBlueprintEditor;
};
