// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyList.h"

#include "PropertyManager.h"
#include "PropertyProxy.h"
#include "WidgetType.h"
#include "Components/TextBlock.h"
#include "MVVM/PropertyListViewModel.h"
#include "UMG/PropertyListItem.h"
#include "UWidget/GenericListView.h"

void UPropertyList::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsDesignTime())
	{
		OnPropertyCategoryChanged(IsValid(PropertyListViewModel) ? PropertyListViewModel->PropertyCategory : FText::FromString(TEXT("Property Category")));
		OnPropertyProxyClassChanged(IsValid(PropertyListViewModel) ? PropertyListViewModel->PropertyProxyClass : nullptr);
	}
}

void UPropertyList::NativeConstruct()
{
	Super::NativeConstruct();
	SetPropertyListViewModel(PropertyListViewModel);
}

void UPropertyList::NativeDestruct()
{
	Super::NativeDestruct();

	if (!IsDesignTime() && IsValid(PropertyProxy))
	{
		FPropertyHelper::UnRegisterPropertyProxy(PropertyProxy);
	}
}

UPropertyListViewModel* UPropertyList::GetPropertyListViewModel()
{
	return PropertyListViewModel;
}

void UPropertyList::SetPropertyListViewModel(UPropertyListViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(PropertyListViewModel)

	PropertyListViewModel = InViewModel;

	if (PropertyListViewModel)
	{
		REGISTER_MVVM_PROPERTY(PropertyListViewModel, PropertyCategory, OnPropertyCategoryChanged, true)
		REGISTER_MVVM_PROPERTY(PropertyListViewModel, PropertyProxyClass, OnPropertyProxyClassChanged, true)
	}
	else
	{
		FPropertyHelper::UnRegisterPropertyProxy(PropertyProxy);
	}
}

UPropertyProxy* UPropertyList::GetPropertyProxy()
{
	return PropertyProxy;
}

void UPropertyList::OnPropertyCategoryChanged_Implementation(const FText& InCategory)
{
	if (Text_PropertyCategory)
	{
		Text_PropertyCategory->SetText(InCategory);
	}
}

void UPropertyList::OnPropertyProxyClassChanged_Implementation(TSubclassOf<UPropertyProxy> InClass)
{
	/* Clear Property Proxy */
	if (PropertyProxy)
	{
		if (IsDesignTime())
		{
			PropertyProxy->NativeOnDestroy();
		}
		else
		{
			FPropertyHelper::UnRegisterPropertyProxy(PropertyProxy);
		}

		PropertyProxy = nullptr;
	}

	/* Clear List View Items */
	if (GenericListView_Property)
	{
		GenericListView_Property->ClearListItems();

		/* Generate New Property Proxy */
		if (InClass)
		{
			if (IsDesignTime())
			{
				PropertyProxy = NewObject<UPropertyProxy>(this, InClass);
				PropertyProxy->NativeOnCreate();
			}
			else
			{
				PropertyProxy = FPropertyHelper::RegisterPropertyProxy(PropertyListViewModel->PropertyProxyTag, InClass);
			}
		}

		/* Generate New List View Items */
		if (PropertyProxy)
		{
			TArray<UPropertyListItemObject*> PropertyListItemObjects;
			for (auto& Object : PropertyProxy->GetPropertyListItemObjects())
			{
				GenericListView_Property->AddItem(Object);
			}
		}
	}
}
