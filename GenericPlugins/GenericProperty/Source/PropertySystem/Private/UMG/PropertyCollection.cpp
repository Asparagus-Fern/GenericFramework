// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyCollection.h"

#include "PropertyCollectionAsset.h"
#include "PropertyProxy.h"
#include "WidgetType.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/VerticalBox.h"
#include "MVVM/PropertyCollectionViewModel.h"
#include "MVVM/PropertyListViewModel.h"
#include "UMG/PropertyList.h"

void UPropertyCollection::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (PropertyDataCollection)
	{
		SetPropertyCollectionAsset(PropertyDataCollection);
	}
	else
	{
		if (ScrollBox_PropertyCollection)
		{
			ScrollBox_PropertyCollection->ClearChildren();
		}
	}
}

void UPropertyCollection::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyCollection::SetPropertyCollectionAsset(UPropertyCollectionAsset* InPropertyCollectionAsset)
{
	if (!IsValid(InPropertyCollectionAsset))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDataCollection Is InValid"));
		return;
	}

	SetPropertyCollectionViewModel(InPropertyCollectionAsset->PropertyCollectionViewModel);
}

void UPropertyCollection::SetPropertyCollectionViewModel(UPropertyCollectionViewModel* InViewModel)
{
	if (ScrollBox_PropertyCollection)
	{
		ScrollBox_PropertyCollection->ClearChildren();
	}

	if (IsDesignTime())
	{
		if (IsValid(InViewModel))
		{
			OnPropertyListViewModelsChanged(InViewModel->PropertyListViewModels);
		}
	}
	else
	{
		UNREGISTER_MVVM_PROPERTY(PropertyCollectionViewModel)
		PropertyCollectionViewModel = InViewModel;
		REGISTER_MVVM_PROPERTY(PropertyCollectionViewModel, PropertyListViewModels, OnPropertyListViewModelsChanged, true)
	}
}

void UPropertyCollection::ClearPropertyCollectionViewModel()
{
	SetPropertyCollectionViewModel(nullptr);
}

void UPropertyCollection::GetAllPropertyProxy(TArray<UPropertyProxy*>& Result) const
{
	for (auto& PropertyList : PropertyListArray)
	{
		Result.Add(PropertyList->GetPropertyProxy());
	}
}

void UPropertyCollection::ApplyPropertyChanged()
{
	TArray<UPropertyProxy*> AllPropertyProxy;
	GetAllPropertyProxy(AllPropertyProxy);

	for (auto& PropertyProxy : AllPropertyProxy)
	{
		PropertyProxy->ApplyProperty();
	}
}

void UPropertyCollection::ResetPropertyChanged()
{
	TArray<UPropertyProxy*> AllPropertyProxy;
	GetAllPropertyProxy(AllPropertyProxy);

	for (auto& PropertyProxy : AllPropertyProxy)
	{
		PropertyProxy->ResetProperty();
	}
}

void UPropertyCollection::OnPropertyListViewModelsChanged_Implementation(const TArray<UPropertyListViewModel*>& InViewModels)
{
	if (ScrollBox_PropertyCollection)
	{
		ScrollBox_PropertyCollection->ClearChildren();
		PropertyListArray.Reset();

		for (int32 i = 0; i < InViewModels.Num(); i++)
		{
			UPropertyListViewModel* ViewModel = InViewModels[i];

			if (ViewModel->PropertyListClass)
			{
				UPropertyList* NewPropertyList = CreateWidget<UPropertyList>(this, ViewModel->PropertyListClass);

				if (!IsDesignTime())
				{
					NewPropertyList->SetPropertyListViewModel(ViewModel);
					
					if (UPropertyProxy* PropertyProxy = NewPropertyList->GetPropertyProxy())
					{
						PropertyProxy->SetIsPropertyEditable(bIsEditable);
					}

					PropertyListArray.Add(NewPropertyList);
				}

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
