// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyProxy.h"

#include "PropertyVisualData.h"
#include "MVVM/PropertyViewModel.h"
#include "UMG/PropertyListItem.h"
#include "UMG/PropertyValue/PropertyValueBase.h"

UPropertyProxy::UPropertyProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UPropertyVisualData* DefaultVisualData = LoadObject<UPropertyVisualData>(nullptr, TEXT("/GenericProperty/DataAsset/DA_PropertyVisualData.DA_PropertyVisualData"));
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

	GeneratePropertyListItemObjects(PropertyViewModels);

	/* Initialize Property And Make List Item Object */
	for (auto& PropertyViewModel : PropertyViewModels)
	{
		if (PropertyViewModel->Initialize(this))
		{
			UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
			NewItemObject->PropertyViewModel = PropertyViewModel;
			NewItemObject->PropertyValueClass = PropertyVisualData->GatherPropertyValueWidgetClass(PropertyViewModel);
			NewItemObject->PropertyOptionClasses = PropertyVisualData->GatherPropertyOptionClasses(PropertyViewModel);
			PropertyListItemObjects.Add(NewItemObject);

			PropertyViewModel->GetOnPropertyApplyEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyApplied));
			PropertyViewModel->GetOnPropertyResetEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyReset));
			PropertyViewModel->GetOnPropertyChangedEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(ThisClass, OnPropertyChanged));

			PropertyViewModel->Startup();
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
			ItemObject->PropertyViewModel->GetOnPropertyResetEvent().RemoveAll(this);
			ItemObject->PropertyViewModel->GetOnPropertyChangedEvent().RemoveAll(this);
		}
	}
}

TArray<UPropertyViewModel*> UPropertyProxy::GetPropertyViewModels() const
{
	return PropertyViewModels;
}

TArray<UPropertyListItemObject*> UPropertyProxy::GetPropertyListItemObjects() const
{
	return PropertyListItemObjects;
}

FGameplayTag UPropertyProxy::GetPropertyProxyTag() const
{
	return ProxyTag;
}

void UPropertyProxy::SetPropertyProxyTag(FGameplayTag InProxyTag)
{
	ProxyTag = InProxyTag;
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

bool UPropertyProxy::IsAnyPropertyValueDirty() const
{
	return !DirtyPropertyViewModels.IsEmpty();
}

void UPropertyProxy::GeneratePropertyListItemObjects_Implementation(TArray<UPropertyViewModel*>& Result)
{
}

void UPropertyProxy::OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel)
{
	if (DirtyPropertyViewModels.Contains(InPropertyViewModel))
	{
		DirtyPropertyViewModels.Remove(InPropertyViewModel);
	}
}

void UPropertyProxy::OnPropertyReset_Implementation(UPropertyViewModel* InPropertyViewModel)
{
	if (DirtyPropertyViewModels.Contains(InPropertyViewModel))
	{
		DirtyPropertyViewModels.Remove(InPropertyViewModel);
	}
}

void UPropertyProxy::OnPropertyChanged_Implementation(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason)
{
	if (!DirtyPropertyViewModels.Contains(InPropertyViewModel))
	{
		DirtyPropertyViewModels.Add(InPropertyViewModel);
	}

	/* When a Property Changed, If bIsDirtyProxy Is true, Update All Property In This Proxy except The Already Changed One */
	if (InPropertyViewModel->GetIsDirtyProxy())
	{
		InPropertyViewModel->Apply();

		for (auto& ItemObject : PropertyListItemObjects)
		{
			if (ItemObject->PropertyViewModel != InPropertyViewModel)
			{
				ItemObject->PropertyViewModel->NotifyPropertyChanged(EPropertyChangedReason::Changed);
			}
		}
	}
}
