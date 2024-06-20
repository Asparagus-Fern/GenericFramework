// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerEditorType.h"
#include "Manager/CoreManager.h"
#include "Manager/ManagerEdInterface.h"
#include "Slate/SManagerEditor.h"
#include "ManagerEditor.generated.h"

class ILevelEditor;

/**
 * 
 */
UCLASS()
class MANAGERVISUALIZATION_API UManagerEditor : public UCoreManager, public IManagerEdInterface
{
	GENERATED_BODY()

public:
	UManagerEditor();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	static UManagerEditor* Get();

	/* IManagerInterface */
public:
	virtual bool IsEditorManager() override { return true; }

	/* IEdManagerInterface */
public:
	virtual void InitCommandList(TSharedPtr<FUICommandList>& InCommandList) override;
	virtual void ExtendToolBar(FToolMenuSection& InSection) override;
	virtual void ExtendToolBarMenu(UToolMenu* InToolMenu) override;

	/* UManagerEditor */
protected:
	void OnLevelEditorCreated(TSharedPtr<ILevelEditor> LevelEditor);

	static FName ManagerEditorTabName;
	TWeakPtr<SDockTab> ManagerEditorTab;
	TSharedPtr<SManagerEditor> ManagerEditorPtr;

	static void OpenManagerEditor();
	TSharedRef<SDockTab> SpawnManagerEditorTab(const FSpawnTabArgs& Args);
	void OnManagerEditorClose(TSharedRef<SDockTab> InDockTab);

public:
	FListViewBase<FManagerListViewInfo, FManagerListViewItem>* ManagerListView = nullptr;
	FListViewBase<FManagerListViewInfo, FManagerListViewItem>*& GetManagerListView() { return ManagerListView; }
};
