// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PropertyDetailPanel.h"

#include "Collection/PropertyCollection.h"
#include "Components/TextBlock.h"
#include "Widget/ListView/PropertyListView.h"

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

void UPropertyDetailPanel::UpdatePropertyDetail(UPropertyCollection* InPropertyCollection)
{
	if (!ensure(Text_Title) || !ensure(Text_TitleDescription) || !ensure(ListView_Property))
	{
		return;
	}

	ListView_Property->ClearListItems();

	if (!InPropertyCollection)
	{
		Text_Title->SetText(LOCTEXT("Message_PropertyDetailPanel_MissingPropertyForTitle", "Property Title Text"));
		Text_TitleDescription->SetText(LOCTEXT("Message_PropertyDetailPanel_MissingPropertyForTitleDescription", "Property Title Description Text"));

		return;
	}

	Text_Title->SetText(InPropertyCollection->GetDisplayName());
	Text_TitleDescription->SetText(InPropertyCollection->GetDescriptionText());
	
	for (const auto& PropertyEntrty : InPropertyCollection->GetChildProperties())
	{
		ListView_Property->AddItem(PropertyEntrty);
	}
}

#undef LOCTEXT_NAMESPACE
