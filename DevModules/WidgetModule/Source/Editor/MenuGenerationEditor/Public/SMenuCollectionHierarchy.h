// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "GameplayTagContainer.h"
#include "SMenuCollectionHierarchyRow.h"
#include "Widgets/SCompoundWidget.h"

class UMenuEntity;
class UMenuCollection;

/**
 * 
 */
class SMenuCollectionHierarchy : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMenuCollectionHierarchy)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor);
	void RefreshHierarchy();

protected:
	TSharedRef<ITableRow> OnGenerateHierarchyRow(FMenuCollectionHierarchyRowPtr Row, const TSharedRef<STableViewBase>& OwnerTable);
	void OnGetHierarchyRowChildren(FMenuCollectionHierarchyRowPtr Row, TArray<FMenuCollectionHierarchyRowPtr>& OutChildren);
	void OnItemSelectionChanged(FMenuCollectionHierarchyRowPtr InItem, ESelectInfo::Type SelectInfo);
	void OnItemDoubleClicked(FMenuCollectionHierarchyRowPtr InItem);
	
private:
	TSharedPtr<SOverlay> ContentOverlay = nullptr;
	TWeakPtr<FBlueprintEditor> BlueprintEditor = nullptr;
	TObjectPtr<UBlueprint> Blueprint = nullptr;

	TArray<FMenuCollectionHierarchyRowPtr> TreeViewRootObjects;
	TMap<FGameplayTag, FMenuCollectionHierarchyRowPtr> TreeViewObjects;
	TSharedPtr<STreeView<FMenuCollectionHierarchyRowPtr>> HierarchyTreeView;

	FReply HandleRefreshHierarchy();
	FReply HandleGenerateHierarchy();

	UMenuCollection* GetMenuCollectionCDO();
	void MakeErrorHierarchy() const;
};
