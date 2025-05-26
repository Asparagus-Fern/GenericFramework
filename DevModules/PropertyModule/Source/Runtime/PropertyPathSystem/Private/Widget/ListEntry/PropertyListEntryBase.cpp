// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Widget/ListEntry/PropertyListEntryBase.h"

#include "Base/PropertyEntity.h"

void UPropertyListEntryBase::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	StopAllAnimations();

	if (ensure(PropertyEntity))
	{
		PropertyEntity->OnPropertyChangedEvent.RemoveAll(this);
		PropertyEntity->OnPropertyEditConditionChangedEvent.RemoveAll(this);
	}

	PropertyEntity = nullptr;
}

void UPropertyListEntryBase::SetPropertyEntity(UPropertyEntity* InProperty)
{
	check(InProperty);

	PropertyEntity = InProperty;
	PropertyEntity->OnPropertyChangedEvent.AddUObject(this, &UPropertyListEntryBase::HandlePropertyChanged);
	PropertyEntity->OnPropertyEditConditionChangedEvent.AddUObject(this, &UPropertyListEntryBase::HandlePropertyEditConditionChanged);

	HandlePropertyEditConditionChanged(PropertyEntity);
}

void UPropertyListEntryBase::OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson)
{
}

void UPropertyListEntryBase::OnPropertyEditConditionChanged(UPropertyEntity* InProperty)
{
	const FPropertyEditableState EditableState = InProperty->GetPropertyEditableState();
	RefreshEditableState(EditableState);
}

void UPropertyListEntryBase::RefreshEditableState(FPropertyEditableState InEditableState)
{
}

void UPropertyListEntryBase::HandlePropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson)
{
	if (!bSuspendChangeUpdates)
	{
		OnPropertyChanged(InProperty, Reson);
	}
}

void UPropertyListEntryBase::HandlePropertyEditConditionChanged(UPropertyEntity* InProperty)
{
	OnPropertyEditConditionChanged(InProperty);
}
