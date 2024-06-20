// Fill out your copyright notice in the Description page of Project Settings.


#include "STestPanel_Editor.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

// void STestPanel_Editor::Construct(const FArguments& InArgs)
// {
// 	ChildSlot
// 	[
// 		SNew(SOverlay)
//
// 		+ SOverlay::Slot()
// 		.HAlign(HAlign_Fill)
// 		.VAlign(VAlign_Fill)
// 		[
// 			SNew(SBorder)
// 			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
// 		]
//
// 		+ SOverlay::Slot()
// 		.HAlign(HAlign_Fill)
// 		.VAlign(VAlign_Fill)
// 		[
// 			SNew(SVerticalBox)
//
// 			+ SVerticalBox::Slot()
// 			.AutoHeight()
// 			[
// 				SNew(SHorizontalBox)
//
// 				+ SHorizontalBox::Slot()
// 				.AutoWidth()
// 				[
// 					InitTestEntry()
// 				]
// 			]
// 		]
// 	];
//
// 	TSharedPtr<FEntry> Entry = FEntryModule::FindEntry("TestEntry");
// 	if (Entry.IsValid())
// 	{
// 		
// 	}
// }
//
// TSharedRef<SWidget> STestPanel_Editor::InitTestEntry()
// {
// 	TestEntry = FEntryModule::RegisterEntry("TestEntry");
//
// 	{
// 		TestEntry->InitEntryWidget<FMenuEntryWidget>
// 		(
// 			"MenuEntryWidget",
// 			FText::FromString("MenuEntryWidget"),
// 			nullptr,
// 			FText::FromString("MenuEntryWidget ToolTip")
// 		);
//
// 		TestEntry->InitEntryWidget<FMenuEntryWidget_Button>
// 		(
// 			"MenuEntryWidget_Button",
// 			FText::FromString("MenuEntryWidget_Button"),
// 			nullptr,
// 			FText::FromString("MenuEntryWidget_Button ToolTip")
// 		);
//
// 		TestEntry->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 		(
// 			"MenuEntryWidget_CheckBox",
// 			FText::FromString("MenuEntryWidget_CheckBox"),
// 			nullptr,
// 			FText::FromString("MenuEntryWidget_CheckBox ToolTip")
// 		);
// 	}
//
// 	{
// 		TSharedRef<FEntryWidgetGroup> Group1 = TestEntry->InitEntryWidgetGroup("Group1");
//
// 		Group1->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 		(
// 			"MenuEntryWidget_CheckBox1",
// 			FText::FromString("Group1_CheckBox1"),
// 			nullptr,
// 			FText::FromString("Group1_CheckBox1")
// 		);
//
// 		Group1->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 		(
// 			"MenuEntryWidget_CheckBox2",
// 			FText::FromString("Group1_CheckBox2"),
// 			nullptr,
// 			FText::FromString("Group1_CheckBox2")
// 		);
//
// 		Group1->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 		(
// 			"MenuEntryWidget_CheckBox3",
// 			FText::FromString("Group1_CheckBox3"),
// 			nullptr,
// 			FText::FromString("Group1_CheckBox3")
// 		);
// 	}
//
// 	{
// 		TSharedRef<FEntryWidgetGroup> Group2 = TestEntry->InitEntryWidgetGroup("Group2");
//
// 		Group2->InitEntryWidget<FMenuEntryWidget_ComboButton>
// 		(
// 			"MenuEntryWidget_ComboButton1",
// 			FText::FromString("Group2_ComboButton1"),
// 			nullptr,
// 			FText::FromString("Group2_ComboButton1"),
// 			FOnGetContent::CreateSP(this, &STestPanel_Editor::OnGetComboButton1Menu)
// 		);
//
// 		Group2->InitEntryWidget<FMenuEntryWidget_ComboButton>
// 		(
// 			"MenuEntryWidget_ComboButton2",
// 			FText::FromString("Group2_ComboButton2"),
// 			nullptr,
// 			FText::FromString("Group2_ComboButton2"),
// 			FOnGetContent::CreateSP(this, &STestPanel_Editor::OnGetComboButton2Menu)
// 		);
//
// 		Group2->InitEntryWidget<FMenuEntryWidget_ComboButton>
// 		(
// 			"MenuEntryWidget_ComboButton3",
// 			FText::FromString("Group2_ComboButton3"),
// 			nullptr,
// 			FText::FromString("Group2_ComboButton3"),
// 			FOnGetContent::CreateSP(this, &STestPanel_Editor::OnGetComboButton3Menu)
// 		);
// 	}
//
// 	return TestEntry->GetGeneratedWidget();
// }
//
// TSharedRef<SWidget> STestPanel_Editor::OnGetComboButton1Menu()
// {
// 	TSharedRef<FEntry> TestMenuEntry1 = FEntryModule::RegisterEntry("TestMenuEntry1", EPanelType::Vertical);
//
// 	TestMenuEntry1->InitEntryWidget<FMenuEntryWidget_ComboButton>
// 	(
// 		"ComboButton1_Menu1",
// 		FText::FromString("ComboButton1_Menu1"),
// 		nullptr,
// 		FText::FromString("ComboButton1_Menu1 ToolTip"),
// 		FOnGetContent::CreateSP(this, &STestPanel_Editor::OnGetMenu1SubMenu),
// 		EMenuPlacement::MenuPlacement_MenuRight
// 	);
//
// 	TestMenuEntry1->InitEntryWidget<FMenuEntryWidget_ComboButton>
// 	(
// 		"ComboButton1_Menu2",
// 		FText::FromString("ComboButton1_Menu2"),
// 		nullptr,
// 		FText::FromString("ComboButton1_Menu2 ToolTip"),
// 		FOnGetContent::CreateSP(this, &STestPanel_Editor::OnGetMenu2SubMenu),
// 		EMenuPlacement::MenuPlacement_MenuRight
// 	);
//
// 	TestMenuEntry1->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 	(
// 		"ComboButton1_Menu3",
// 		FText::FromString("ComboButton1_Menu3"),
// 		nullptr,
// 		FText::FromString("ComboButton1_Menu3 ToolTip")
// 	);
//
// 	TestMenuEntry1->InitEntryWidget<FMenuEntryWidget_Button>
// 	(
// 		"ComboButton1_Menu4",
// 		FText::FromString("ComboButton1_Menu4"),
// 		nullptr,
// 		FText::FromString("ComboButton1_Menu4 ToolTip")
// 	);
//
// 	return TestMenuEntry1->GetGeneratedWidget();
// }
//
// TSharedRef<SWidget> STestPanel_Editor::OnGetComboButton2Menu()
// {
// 	TSharedRef<FEntry> TestMenuEntry2 = FEntryModule::RegisterEntry("TestMenuEntry2", EPanelType::Vertical);
//
// 	TestMenuEntry2->InitEntryWidget<FMenuEntryWidget_Button>
// 	(
// 		"ComboButton2_Menu1",
// 		FText::FromString("ComboButton2_Menu1"),
// 		nullptr,
// 		FText::FromString("ComboButton2_Menu1 ToolTip")
// 	);
//
// 	TestMenuEntry2->InitEntryWidget<FMenuEntryWidget_Button>
// 	(
// 		"ComboButton2_Menu2",
// 		FText::FromString("ComboButton2_Menu2"),
// 		nullptr,
// 		FText::FromString("ComboButton2_Menu2 ToolTip")
// 	);
//
// 	return TestMenuEntry2->GetGeneratedWidget();
// }
//
// TSharedRef<SWidget> STestPanel_Editor::OnGetComboButton3Menu()
// {
// 	TSharedRef<FEntry> TestMenuEntry3 = FEntryModule::RegisterEntry("TestMenuEntry3", EPanelType::Vertical);
//
// 	TestMenuEntry3->InitEntryWidget<FMenuEntryWidget_Button>
// 	(
// 		"ComboButton3_Menu1",
// 		FText::FromString("ComboButton3_Menu1"),
// 		nullptr,
// 		FText::FromString("ComboButton3_Menu1 ToolTip")
// 	);
//
// 	TestMenuEntry3->InitEntryWidget<FMenuEntryWidget_Button>
// 	(
// 		"ComboButton3_Menu2",
// 		FText::FromString("ComboButton3_Menu2"),
// 		nullptr,
// 		FText::FromString("ComboButton3_Menu2 ToolTip")
// 	);
//
// 	return TestMenuEntry3->GetGeneratedWidget();
// }
//
// TSharedRef<SWidget> STestPanel_Editor::OnGetMenu1SubMenu()
// {
// 	TSharedRef<FEntry> TestSubMenuEntry1 = FEntryModule::RegisterEntry("TestSubMenuEntry1", EPanelType::Vertical);
//
// 	TestSubMenuEntry1->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 	(
// 		"Menu1_SubMenu1",
// 		FText::FromString("Menu1_SubMenu1"),
// 		nullptr,
// 		FText::FromString("Menu1_SubMenu1 ToolTip")
// 	);
//
// 	TestSubMenuEntry1->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 	(
// 		"Menu1_SubMenu2",
// 		FText::FromString("Menu1_SubMenu2"),
// 		nullptr,
// 		FText::FromString("Menu1_SubMenu2 ToolTip")
// 	);
//
// 	return TestSubMenuEntry1->GetGeneratedWidget();
// }
//
// TSharedRef<SWidget> STestPanel_Editor::OnGetMenu2SubMenu()
// {
// 	TSharedRef<FEntry> TestSubMenuEntry2 = FEntryModule::RegisterEntry("TestSubMenuEntry2", EPanelType::Vertical);
//
// 	TestSubMenuEntry2->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 	(
// 		"Menu2_SubMenu1",
// 		FText::FromString("Menu2_SubMenu1"),
// 		nullptr,
// 		FText::FromString("Menu2_SubMenu1 ToolTip")
// 	);
//
// 	TestSubMenuEntry2->InitEntryWidget<FMenuEntryWidget_CheckBox>
// 	(
// 		"Menu2_SubMenu2",
// 		FText::FromString("Menu2_SubMenu2"),
// 		nullptr,
// 		FText::FromString("Menu2_SubMenu2 ToolTip")
// 	);
//
// 	return TestSubMenuEntry2->GetGeneratedWidget();
// }

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
