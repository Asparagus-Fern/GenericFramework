// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyListItem.h"

#include "GenericWidgetSubsystem.h"
#include "PropertyType.h"
#include "WidgetType.h"
#include "Components/TextBlock.h"
#include "MVVM/PropertyViewModel.h"
#include "UMG/PropertyListItemOption.h"
#include "UMG/Spawner/PropertyValueSpawner.h"

void UPropertyListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UPropertyListItemObject* PropertyListItemObject = GetListItem<UPropertyListItemObject>())
	{
		PropertyViewModel = PropertyListItemObject->PropertyViewModel;

		REGISTER_MVVM_PROPERTY(PropertyViewModel, PropertyDisplayName, OnPropertyDisplayNameChanged, true)
		PropertyViewModel->GetOnPropertyTagAddedEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(UPropertyListItem, OnPropertyTagAdded));
		PropertyViewModel->GetOnPropertyTagRemovedEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(UPropertyListItem, OnPropertyTagRemoved));

		for (auto& PropertyTag : PropertyViewModel->PropertyTags)
		{
			if (PropertyListItemObject->PropertyOptionClasses.Contains(PropertyTag))
			{
				AddPropertyOption(PropertyTag, PropertyListItemObject->PropertyOptionClasses.FindRef(PropertyTag));
			}
		}

		if (PropertyValueSpawner)
		{
			PropertyValueSpawner->SpawnPropertyWidget(PropertyListItemObject->PropertyValueClass, PropertyViewModel);
		}
	}
}

void UPropertyListItem::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

void UPropertyListItem::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);
}

void UPropertyListItem::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	if (PropertyViewModel)
	{
		PropertyViewModel->RemoveAllFieldValueChangedDelegates(this);
		PropertyViewModel->GetOnPropertyTagAddedEvent().RemoveAll(this);
		PropertyViewModel->GetOnPropertyTagRemovedEvent().RemoveAll(this);
	}
}

void UPropertyListItem::OnPropertyDisplayNameChanged_Implementation(const FText& InDisplayName)
{
	if (Text_PropertyName)
	{
		Text_PropertyName->SetText(InDisplayName);
	}
}

void UPropertyListItem::OnPropertyTagAdded_Implementation(FGameplayTag InPropertyTag)
{
	if (UPropertyListItemObject* PropertyListItemObject = GetListItem<UPropertyListItemObject>())
	{
		if (PropertyListItemObject->PropertyOptionClasses.Contains(InPropertyTag))
		{
			AddPropertyOption(InPropertyTag, PropertyListItemObject->PropertyOptionClasses.FindRef(InPropertyTag));
		}
	}
}

void UPropertyListItem::OnPropertyTagRemoved_Implementation(FGameplayTag InPropertyTag)
{
	RemovePropertyOption(InPropertyTag);
}

void UPropertyListItem::AddPropertyOption(FGameplayTag InPropertyTag, TSubclassOf<UPropertyListItemOption> InClass)
{
	if (!InPropertyTag.IsValid())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyTag Is InValid"))
		return;
	}

	if (!InClass)
	{
		GenericLOG(GenericLogProperty, Error, TEXT("Property Option Class Is InValid"))
		return;
	}

	if (PropertyOptions.Contains(InPropertyTag))
	{
		return;
	}

	if (UGenericWidgetSubsystem* GenericWidgetSubsystem = UGenericWidgetSubsystem::Get(this))
	{
		UPropertyListItemOption* NewPropertyOption = GenericWidgetSubsystem->OpenGenericWidget<UPropertyListItemOption>(this, InClass);
		if (IsValid(NewPropertyOption))
		{
			NewPropertyOption->SetPropertyViewModel(PropertyViewModel);
			PropertyOptions.Add(InPropertyTag, NewPropertyOption);

			if (Panel_PropertyOption)
			{
				Panel_PropertyOption->AddChild(NewPropertyOption);
			}
		}
	}
}

void UPropertyListItem::RemovePropertyOption(FGameplayTag InPropertyTag)
{
	if (!InPropertyTag.IsValid())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyTag Is InValid"))
		return;
	}

	if (!PropertyOptions.Contains(InPropertyTag))
	{
		return;
	}

	UPropertyListItemOption* RemoveOption = PropertyOptions.FindRef(InPropertyTag);
	PropertyOptions.Remove(InPropertyTag);

	if (Panel_PropertyOption)
	{
		Panel_PropertyOption->RemoveChild(RemoveOption);
	}
}
