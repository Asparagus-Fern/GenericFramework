// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ManagerEditorType.h"
#include "Procedure/ProcedureInterface.h"
#include "Widgets/SCompoundWidget.h"


/**
 * 
 */
class MANAGERVISUALIZATION_API SManagerEditor : public SCompoundWidget, public IProcedureBaseInterface
{
public:
	SLATE_BEGIN_ARGS(SManagerEditor)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& InDockTab);

	/* IProcedureInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

protected:
	TWeakPtr<SDockTab> ParentDockTab;
	TSharedPtr<FTabManager> TabManager;

	static FName ManagerEditorToolBarName;
	TSharedRef<SWidget> RegisterManagerEditorToolBar();

	static FName ManagerListTabID;
	static FName ManagerDetailTabID;
	TSharedRef<SDockTab> SpawnManagerListTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnManagerDetailTab(const FSpawnTabArgs& Args);

	TSharedPtr<IDetailsView> DetailsView;
	TArray<FManagerListViewItemPtr> ManagerListViewItems;
	TSharedRef<ITableRow> OnGenerateRow(FManagerListViewItemPtr InItem, const TSharedRef<class STableViewBase>& Owner);
	void OnSelectionChanged(FManagerListViewItemPtr InItem, ESelectInfo::Type SelectInfo);
};
