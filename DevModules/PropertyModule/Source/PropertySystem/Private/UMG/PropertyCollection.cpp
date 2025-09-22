// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyCollection.h"

#include "WidgetType.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/VerticalBox.h"
#include "MVVM/PropertyCollectionViewModel.h"
#include "MVVM/PropertyListViewModel.h"
#include "UMG/PropertyList.h"

void UPropertyCollection::SetPropertyCollectionViewModel(UPropertyCollectionViewModel* InViewModel)
{
	if (PropertyCollectionViewModel)
	{
		if (ScrollBox_PropertyCollection)
		{
			ScrollBox_PropertyCollection->ClearChildren();
		}
		
		for (auto& PropertyList : PropertyLists)
		{
			PropertyList->SetPropertyListViewModel(nullptr);
		}
		
		PropertyLists.Reset();
		PropertyCollectionViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	PropertyCollectionViewModel = InViewModel;

	if (PropertyCollectionViewModel)
	{
		REGISTER_MVVM_PROPERTY(PropertyCollectionViewModel, PropertyListViewModels, OnPropertyListViewModelsChanged, true)
	}
}

void UPropertyCollection::OnPropertyListViewModelsChanged_Implementation(const TArray<UPropertyListViewModel*>& InViewModels)
{
	for (auto& PropertyList : PropertyLists)
	{
		PropertyList->SetPropertyListViewModel(nullptr);
	}

	PropertyLists.Reset();

	if (ScrollBox_PropertyCollection)
	{
		ScrollBox_PropertyCollection->ClearChildren();

		for (int32 i = 0; i < InViewModels.Num(); i++)
		{
			UPropertyListViewModel* ViewModel = InViewModels[i];

			if (ViewModel->PropertyListClass)
			{
				UPropertyList* NewPropertyList = CreateWidget<UPropertyList>(this, ViewModel->PropertyListClass);
				NewPropertyList->SetPropertyListViewModel(ViewModel);
				PropertyLists.Add(NewPropertyList);

				UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>(ScrollBox_PropertyCollection->AddChild(NewPropertyList));

				FMargin SlotPadding;
				SlotPadding.Top = (i == 0) ? 0.f : Spacing;

				ScrollBoxSlot->SetPadding(SlotPadding);
				ScrollBoxSlot->SetHorizontalAlignment(HAlign_Fill);
				ScrollBoxSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}
	}
}
