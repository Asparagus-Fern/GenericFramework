// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyList.h"

#include "PropertySubsystem.h"
#include "PropertyProxy.h"
#include "PropertyVisualData.h"
#include "WidgetType.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "DataSource/PropertyDataSourceCollection.h"
#include "MVVM/PropertyListViewModel.h"
#include "UMG/PropertyListItem.h"

UPropertyList::UPropertyList(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UPropertyVisualData* DefaultVisualData = LoadObject<UPropertyVisualData>(nullptr, TEXT("/GenericProperty/DataAsset/DA_PropertyVisualData.DA_PropertyVisualData"));
	if (IsValid(DefaultVisualData))
	{
		PropertyVisualData = DefaultVisualData;
	}
}

void UPropertyList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyList::NativeDestruct()
{
	Super::NativeDestruct();

	if (!IsDesignTime() && IsValid(PropertyProxy))
	{
		if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(this))
		{
			PropertySubsystem->UnRegisterPropertyProxy(PropertyProxy);
		}
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
		REGISTER_MVVM_PROPERTY(PropertyListViewModel, PropertyDataSourceCollectionClass, OnPropertyDataSourceCollectionClassChanged, true)
	}
	else
	{
		if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(this))
		{
			PropertySubsystem->UnRegisterPropertyProxy(PropertyProxy);
		}
	}
}

UPropertyProxy* UPropertyList::GetPropertyProxy()
{
	return PropertyProxy;
}

void UPropertyList::RefreshPropertyList()
{
	if (ListView_Property)
	{
		ListView_Property->ClearListItems();
		PropertyListItemObjects.Reset();

		/* Generate New List View Items */
		if (PropertyProxy && PropertyVisualData)
		{
			for (auto& PropertyViewModel : PropertyProxy->GetPropertyViewModels())
			{
				UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
				NewItemObject->PropertyViewModel = PropertyViewModel;
				NewItemObject->PropertyValueClass = PropertyVisualData->GatherPropertyValueWidgetClass(PropertyViewModel);
				NewItemObject->PropertyOptionClasses = PropertyVisualData->GatherPropertyOptionClasses(PropertyViewModel);
				PropertyListItemObjects.Add(NewItemObject);

				ListView_Property->AddItem(NewItemObject);
			}
		}
	}
}

void UPropertyList::OnPropertyCategoryChanged_Implementation(const FText& InCategory)
{
	if (Text_PropertyCategory)
	{
		Text_PropertyCategory->SetText(InCategory);
	}
}

void UPropertyList::OnPropertyDataSourceCollectionClassChanged_Implementation(TSubclassOf<UPropertyDataSourceCollection> InClass)
{
	if (UPropertySubsystem* PropertySubsystem = UPropertySubsystem::Get(this))
	{
		PropertySubsystem->UnRegisterPropertyProxy(PropertyProxy);
		PropertyProxy = PropertySubsystem->RegisterPropertyProxy(PropertyListViewModel->PropertyProxyTag, InClass);
	}

	RefreshPropertyList();
}
