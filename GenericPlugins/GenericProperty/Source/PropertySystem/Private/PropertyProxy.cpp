// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyProxy.h"

#include "PropertyVisualData.h"
#include "DataSource/PropertyDataSourceCollection.h"
#include "MVVM/PropertyViewModel.h"
#include "UMG/PropertyListItem.h"
#include "UMG/PropertyValue/PropertyValueBase.h"

bool UPropertyProxy::Initialize()
{
	PropertyViewModels.Reset();
	PropertyDataSourceCollection->GeneratePropertyViewModels(PropertyViewModels);

	/* Initialize Property And Make List Item Object */
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		if (!PropertyViewModel->Initialize(this))
		{
			GenericLOG(GenericLogProperty, Error, TEXT("PropertyViewModel Initialize Fail!"))
			return false;
		}

		PropertyViewModel->GetOnPropertyApplyEvent().AddUObject(this, &UPropertyProxy::OnPropertyApplied);
		PropertyViewModel->GetOnPropertyResetEvent().AddUObject(this, &UPropertyProxy::OnPropertyReset);
		PropertyViewModel->GetOnPropertyChangedEvent().AddUObject(this, &UPropertyProxy::OnPropertyChanged);

		PropertyViewModel->Startup();
	}

	return true;
}

void UPropertyProxy::Deinitialize()
{
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		PropertyViewModel->Deinitialize();

		PropertyViewModel->GetOnPropertyApplyEvent().RemoveAll(this);
		PropertyViewModel->GetOnPropertyResetEvent().RemoveAll(this);
		PropertyViewModel->GetOnPropertyChangedEvent().RemoveAll(this);
	}
}

const TArray<UPropertyViewModel*>& UPropertyProxy::GetPropertyViewModels() const
{
	return PropertyViewModels;
}

FGameplayTag UPropertyProxy::GetPropertyProxyTag() const
{
	return ProxyTag;
}

void UPropertyProxy::SetPropertyProxyTag(FGameplayTag InProxyTag)
{
	ProxyTag = InProxyTag;
}

UPropertyDataSourceCollection* UPropertyProxy::GetPropertyDataSourceCollection()
{
	return PropertyDataSourceCollection;
}

UPropertyDataSourceCollection* UPropertyProxy::SetPropertyDataSourceCollection(const TSubclassOf<UPropertyDataSourceCollection>& InPropertyDataSourceCollectionClass)
{
	if (!InPropertyDataSourceCollectionClass)
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDataSourceCollectionClass Is InValid"))
		return nullptr;
	}

	UPropertyDataSourceCollection* NewCollection = NewObject<UPropertyDataSourceCollection>(this, InPropertyDataSourceCollectionClass);
	SetPropertyDataSourceCollection(NewCollection);
	return NewCollection;
}

void UPropertyProxy::SetPropertyDataSourceCollection(UPropertyDataSourceCollection* InPropertyDataSourceCollection)
{
	if (!IsValid(InPropertyDataSourceCollection))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("InPropertyDataSourceCollection Is InValid"))
		return;
	}

	PropertyDataSourceCollection = InPropertyDataSourceCollection;
	PropertyDataSourceCollection->SetOwnerPropertyProxy(this);
}

void UPropertyProxy::ApplyProperty()
{
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		PropertyViewModel->Apply();
	}
}

void UPropertyProxy::ResetProperty()
{
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		PropertyViewModel->Reset();
	}
}

void UPropertyProxy::SetIsPropertyEditable(const bool InIsEditable)
{
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		PropertyViewModel->SetIsEditable(InIsEditable);
	}
}

bool UPropertyProxy::IsAnyPropertyValueDirty() const
{
	return !DirtyPropertyViewModels.IsEmpty();
}

void UPropertyProxy::OnPropertyApplied(UPropertyViewModel* InPropertyViewModel)
{
	if (DirtyPropertyViewModels.Contains(InPropertyViewModel))
	{
		DirtyPropertyViewModels.Remove(InPropertyViewModel);
	}

	if (PropertyDataSourceCollection)
	{
		PropertyDataSourceCollection->OnPropertyApplied(InPropertyViewModel);
	}
}

void UPropertyProxy::OnPropertyReset(UPropertyViewModel* InPropertyViewModel)
{
	if (DirtyPropertyViewModels.Contains(InPropertyViewModel))
	{
		DirtyPropertyViewModels.Remove(InPropertyViewModel);
	}

	if (PropertyDataSourceCollection)
	{
		PropertyDataSourceCollection->OnPropertyReset(InPropertyViewModel);
	}
}

void UPropertyProxy::OnPropertyChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason)
{
	if (!DirtyPropertyViewModels.Contains(InPropertyViewModel))
	{
		DirtyPropertyViewModels.Add(InPropertyViewModel);
	}

	if (PropertyDataSourceCollection)
	{
		PropertyDataSourceCollection->OnPropertyChanged(InPropertyViewModel, ChangedReason);
	}

	/* When a Property Changed, If bIsDirtyProxy Is true, Update All Property In This Proxy except The Already Changed One */
	if (InPropertyViewModel->GetIsDirtyProxy())
	{
		InPropertyViewModel->Apply();

		for (auto& PropertyViewModel : PropertyViewModels)
		{
			PropertyViewModel->NotifyPropertyChanged(EPropertyChangedReason::Changed);
		}
	}
}
