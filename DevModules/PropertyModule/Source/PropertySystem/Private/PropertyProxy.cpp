// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyProxy.h"

#include "PropertyVisualData.h"
#include "MVVM/PropertyViewModel.h"
#include "UMG/PropertyListItem.h"
#include "UMG/PropertyValue/PropertyValueBase.h"

UPropertyProxy::UPropertyProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UPropertyVisualData* DefaultVisualData = LoadObject<UPropertyVisualData>(nullptr, TEXT("/PropertyModule/DataAsset/DA_PropertyVisualData.DA_PropertyVisualData"));
	if (IsValid(DefaultVisualData))
	{
		PropertyVisualData = DefaultVisualData;
	}
}

void UPropertyProxy::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	if (!PropertyVisualData)
	{
		GenericLOG(GenericLogProperty, Error, TEXT("Missing Property Visual Data"))
		return;
	}

	TArray<UPropertyViewModel*> PropertyViewModels;
	GeneratePropertyListItemObjects(PropertyViewModels);

	/* Initialize Property And Make List Item Object */
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		if (PropertyViewModel->Initialize(this))
		{
			PropertyViewModel->GetOnPropertyApplyEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyApplied));
			PropertyViewModel->GetOnPropertyReverseEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyReversed));
			PropertyViewModel->GetOnPropertyResetEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyReset));
			PropertyViewModel->GetOnPropertyChangedEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyChanged));

			UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
			NewItemObject->PropertyValueClass = PropertyVisualData->GatherListItemForProperty(PropertyViewModel);
			NewItemObject->PropertyViewModel = PropertyViewModel;
			PropertyListItemObjects.Add(NewItemObject);
		}
	}
}

void UPropertyProxy::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();

	for (auto& ItemObject : PropertyListItemObjects)
	{
		if (ItemObject->PropertyViewModel)
		{
			ItemObject->PropertyViewModel->Deinitialize();

			ItemObject->PropertyViewModel->GetOnPropertyApplyEvent().RemoveAll(this);
			ItemObject->PropertyViewModel->GetOnPropertyReverseEvent().RemoveAll(this);
			ItemObject->PropertyViewModel->GetOnPropertyResetEvent().RemoveAll(this);
			ItemObject->PropertyViewModel->GetOnPropertyChangedEvent().RemoveAll(this);
		}
	}
}

TArray<UPropertyListItemObject*> UPropertyProxy::GetPropertyListItemObjects() const
{
	return PropertyListItemObjects;
}

void UPropertyProxy::ApplyProperty()
{
	for (auto& ItemObject : PropertyListItemObjects)
	{
		if (IsValid(ItemObject->PropertyViewModel))
		{
			ItemObject->PropertyViewModel->Apply();
		}
	}
}

void UPropertyProxy::ReverseProperty()
{
	for (auto& ItemObject : PropertyListItemObjects)
	{
		if (IsValid(ItemObject->PropertyViewModel))
		{
			ItemObject->PropertyViewModel->Reverse();
		}
	}
}

void UPropertyProxy::ResetProperty()
{
	for (auto& ItemObject : PropertyListItemObjects)
	{
		if (IsValid(ItemObject->PropertyViewModel))
		{
			ItemObject->PropertyViewModel->Reset();
		}
	}
}

void UPropertyProxy::GeneratePropertyListItemObjects_Implementation(TArray<UPropertyViewModel*>& Result)
{
}

void UPropertyProxy::OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel)
{
}

void UPropertyProxy::OnPropertyReversed_Implementation(UPropertyViewModel* InPropertyViewModel)
{
}

void UPropertyProxy::OnPropertyReset_Implementation(UPropertyViewModel* InPropertyViewModel)
{
}

void UPropertyProxy::OnPropertyChanged_Implementation(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason)
{
	/* When a Property Changed, If bIsDirtyProxy Is true, Update All Property In This Proxy except The Already Changed One */
	if (InPropertyViewModel->GetIsDirtyProxy())
	{
		for (auto& ItemObject : PropertyListItemObjects)
		{
			if (ItemObject->PropertyViewModel != InPropertyViewModel)
			{
				ItemObject->PropertyViewModel->NotifyPropertyChanged(EPropertyChangedReason::Changed);
			}
		}
	}
}
