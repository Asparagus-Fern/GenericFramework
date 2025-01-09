// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuCollectionHierarchy.h"

#include "SlateOptMacros.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Entity/MenuCollection.h"
#include "Entity/MenuEntity.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMenuCollectionHierarchy::Construct(const FArguments& InArgs, TWeakPtr<FBlueprintEditor> InBlueprintEditor)
{
	BlueprintEditor = InBlueprintEditor;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.f)
			[
				SNew(SButton)
				.Text(FText::FromString("Refresh"))
				.ToolTipText(FText::FromString("Click To Refresh Menu Hierarchy"))
				.OnClicked(this, &SMenuCollectionHierarchy::HandleRefreshHierarchy)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.f)
			[
				SNew(SButton)
				.Text(FText::FromString("Generate"))
				.ToolTipText(FText::FromString("Click To Generate Menu Hierarchy"))
				.OnClicked(this, &SMenuCollectionHierarchy::HandleGenerateHierarchy)
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SAssignNew(ContentOverlay, SOverlay)
		]
	];

	if (BlueprintEditor.IsValid())
	{
		Blueprint = BlueprintEditor.Pin()->GetBlueprintObj();
		RefreshHierarchy();
	}
	else
	{
		MakeErrorHierarchy();
	}
}

void SMenuCollectionHierarchy::RefreshHierarchy()
{
	if (HierarchyTreeView.IsValid())
	{
		ContentOverlay->ClearChildren();
		TreeViewRootObjects.Reset();
		TreeViewObjects.Reset();
		HierarchyTreeView->ClearRootItemsSource();
	}

	if (UMenuCollection* MenuCollection = GetMenuCollectionCDO())
	{
		if (MenuCollection->GetRootMenuEntity())
		{
			for (auto& MenuEntity : MenuCollection->MenuEntities)
			{
				TreeViewObjects.Add(MenuEntity->MenuTag, MakeShared<FMenuCollectionHierarchyRow>(MenuEntity));
			}

			TreeViewRootObjects.Add(MakeShared<FMenuCollectionHierarchyRow>(MenuCollection->GetRootMenuEntity()));

			ContentOverlay->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(HierarchyTreeView, STreeView<FMenuCollectionHierarchyRowPtr>)
					.SelectionMode(ESelectionMode::Single)
					.TreeItemsSource(&TreeViewRootObjects)
					.OnGenerateRow(this, &SMenuCollectionHierarchy::OnGenerateHierarchyRow)
					.OnGetChildren(this, &SMenuCollectionHierarchy::OnGetHierarchyRowChildren)
					.OnSelectionChanged(this, &SMenuCollectionHierarchy::OnSelectionChanged)
				];

			for (auto& TreeViewObject : TreeViewObjects)
			{
				HierarchyTreeView->SetItemExpansion(TreeViewObject.Value, true);
			}

			return;
		}
	}

	MakeErrorHierarchy();
}

TSharedRef<ITableRow> SMenuCollectionHierarchy::OnGenerateHierarchyRow(FMenuCollectionHierarchyRowPtr Row, const TSharedRef<STableViewBase>& OwnerTable)
{
	check(Row.IsValid());

	return SNew(STableRow<FMenuCollectionHierarchyRowPtr>, OwnerTable)
		.ShowWires(true)
		[
			SNew(SMenuCollectionHierarchyRow, Row)
		];
}

void SMenuCollectionHierarchy::OnGetHierarchyRowChildren(FMenuCollectionHierarchyRowPtr Row, TArray<FMenuCollectionHierarchyRowPtr>& OutChildren)
{
	for (auto& ChildTag : UBPFunctions_GameplayTag::GetDirectGameplayTagChildren(Row->GetMenuEntity()->MenuTag))
	{
		OutChildren.Add(TreeViewObjects.FindRef(ChildTag));
	}
}

void SMenuCollectionHierarchy::OnSelectionChanged(FMenuCollectionHierarchyRowPtr InItem, ESelectInfo::Type SelectInfo)
{
}

FReply SMenuCollectionHierarchy::HandleRefreshHierarchy()
{
	RefreshHierarchy();
	return FReply::Handled();
}

FReply SMenuCollectionHierarchy::HandleGenerateHierarchy()
{
	if (UMenuCollection* MenuCollection = GetMenuCollectionCDO())
	{
		MenuCollection->GenerateMenu();
	}
	return FReply::Handled();
}

UMenuCollection* SMenuCollectionHierarchy::GetMenuCollectionCDO()
{
	return Cast<UMenuCollection>(Blueprint->GeneratedClass->ClassDefaultObject);
}

void SMenuCollectionHierarchy::MakeErrorHierarchy() const
{
	ContentOverlay->ClearChildren();

	ContentOverlay->AddSlot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString("InValid Hierarchy"))
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
