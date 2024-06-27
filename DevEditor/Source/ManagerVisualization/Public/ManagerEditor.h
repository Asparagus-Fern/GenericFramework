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

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* IManagerInterface */
public:
	virtual FText GetManagerDisplayName() override;
	virtual bool DoesSupportWorldType(EWorldType::Type InWorldType) override;

	/* IEdManagerInterface */
public:
	virtual void InitCommandList(TSharedPtr<FUICommandList>& InCommandList) override;
	virtual void ExtendToolBar(FToolMenuSection& InSection) override;

	/* UManagerEditor */
protected:
	FDelegateHandle LevelEditorCreatedHandle;
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
