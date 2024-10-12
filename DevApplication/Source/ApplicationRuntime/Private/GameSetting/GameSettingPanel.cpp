// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/GameSettingPanel.h"

#include "Collection/PropertyCollection.h"
#include "Components/TextBlock.h"
#include "Widget/PropertyDetailPanel.h"
#include "Widget/ListView/PropertyListView.h"

void UGameSettingPanel::NativeConstruct()
{
	Super::NativeConstruct();

	ListView_SettingMenu->OnItemSelectionChanged().AddUObject(this, &UGameSettingPanel::OnSettingMenuSelectionChanged);
}

void UGameSettingPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

void UGameSettingPanel::OnSettingMenuSelectionChanged(UObject* InObject)
{
	if (UPropertyCollection* PropertyCollectionItem = Cast<UPropertyCollection>(InObject))
	{
		Panel_ProertyDetail->UpdatePropertyDetail(PropertyCollectionItem);
	}
}

void UGameSettingPanel::RefreshPropertyWidget()
{
	// Super::RefreshPropertyWidget();

	if (Text_Setting)
	{
		Text_Setting->SetText(PropertyCollection->GetDisplayName());
	}

	if (Text_SettingDescription)
	{
		Text_SettingDescription->SetText(PropertyCollection->GetDescriptionText());
	}

	for (const auto& ChildCollection : PropertyCollection->GetChildCollections())
	{
		ListView_SettingMenu->AddItem(ChildCollection);
	}
}
