// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/GameSettingPanel.h"

#include "Collection/PropertyCollection.h"
#include "Components/TextBlock.h"
#include "GameSetting/GameSettingRegistry.h"
#include "Widget/ListView/PropertyListView.h"

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

void UGameSettingPanel::SetupProperty()
{
	Super::SetupProperty();

	DEnsureAlwaysLOG(DLogDefault, GetRegistry<UGameSettingRegistry>())
	
	SetPropertyCollection(GetRegistry<UGameSettingRegistry>()->GetGameSettingCollection());

	ListView_SettingMenu->OnItemSelectionChanged().AddUObject(this, &UGameSettingPanel::OnSettingMenuSelectionChanged);
	if (ListView_SettingMenu->GetNumItems() > 0)
	{
		ListView_SettingMenu->SetSelectedIndex(0);
	}
}

void UGameSettingPanel::ClearupProperty()
{
	ListView_SettingMenu->OnItemSelectionChanged().RemoveAll(this);
	Super::ClearupProperty();
}

void UGameSettingPanel::Refresh()
{
	// Super::Refresh();

	RefreshPropertyWidget(nullptr);

	if (Text_SettingTitle)
	{
		Text_SettingTitle->SetText(Collection ? Collection->GetDisplayName() : LOCTEXT("Warning_GameSettingPanel_MissingPropertyCollectionForTitle", "Property Title"));
	}

	if (Text_SettingTitleDescription)
	{
		Text_SettingTitleDescription->SetText(Collection ? Collection->GetDescriptionText() : LOCTEXT("Warning_GameSettingPanel_MissingPropertyCollectionForTitleDescription", "Property Title Description"));
	}

	ListView_SettingMenu->ClearListItems();
	for (const auto& ChildCollection : Collection->GetChildCollections())
	{
		ListView_SettingMenu->AddItem(ChildCollection);
	}
}

void UGameSettingPanel::OnSettingMenuSelectionChanged(UObject* InObject)
{
	if (UPropertyCollection* PropertyCollectionItem = Cast<UPropertyCollection>(InObject))
	{
		RefreshPropertyWidget(PropertyCollectionItem);
	}
}

#undef LOCTEXT_NAMESPACE
