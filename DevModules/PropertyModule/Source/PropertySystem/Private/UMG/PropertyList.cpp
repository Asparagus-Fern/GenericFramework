// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyList.h"

#include "PropertyManager.h"
#include "PropertyProxy.h"
#include "Manager/ManagerStatics.h"
#include "UMG/PropertyListItem.h"
#include "UWidget/GenericListView.h"

void UPropertyList::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetPropertyProxyClass(PropertyProxyClass);
}

void UPropertyList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyList::NativeDestruct()
{
	Super::NativeDestruct();

	if (!IsDesignTime())
	{
		if (UPropertyManager* PropertyManager = GetManagerOwner<UPropertyManager>())
		{
			PropertyManager->UnRegisterPropertyProxy(PropertyProxy);
		}
	}
}

void UPropertyList::SetPropertyProxyClass(TSubclassOf<UPropertyProxy> InClass)
{
	GenericListView_Property->ClearListItems();
	PropertyProxyClass = InClass;
	PropertyProxy = nullptr;

	if (PropertyProxyClass)
	{
		if (IsDesignTime())
		{
			UPropertyProxy* NewPropertyProxy = NewObject<UPropertyProxy>();
		}
		else
		{
			if (UPropertyManager* PropertyManager = GetManagerOwner<UPropertyManager>())
			{
				PropertyProxy = PropertyManager->RegisterPropertyProxy(PropertyProxyClass);
			}
		}

		if (IsValid(PropertyProxy))
		{
			TArray<UPropertyListItemObject*> PropertyListItemObjects;
			for (auto& Object : PropertyProxy->GetPropertyListItemObjects())
			{
				GenericListView_Property->AddItem(Object);
			}
		}
	}
}
