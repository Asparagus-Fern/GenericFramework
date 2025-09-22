// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "MVVM/PropertyViewModel.h"

#include "PropertyType.h"
#include "Type/DebugType.h"

UPropertyViewModel::UPropertyViewModel(const FObjectInitializer& FObjectInitializer)
	: Super(FObjectInitializer)
{
}

bool UPropertyViewModel::Initialize(UPropertyProxy* InOwnerProxy)
{
	check(!bIsInitialized)
	check(InOwnerProxy)

	bIsInitialized = true;
	OwnerProxy = InOwnerProxy;

	/* Changed Self When Dependency Property Changed */
	for (const auto& PropertyDependency : PropertyDependencyList)
	{
		PropertyDependency->OnPropertyChangedEvent.AddUObject(this, &UPropertyViewModel::HandleOnPropertyDependencyValueChanged);

		OnPropertyDependencyAdded(PropertyDependency);
		OnPropertyDependencyAddedEvent.Broadcast(PropertyDependency);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDependencyList);
	}

	for (const auto& PropertyTag : PropertyTags)
	{
		OnPropertyTagAdded(PropertyTag);
		OnPropertyTagAddedEvent.Broadcast(this, PropertyTag);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyTags);
	}

	return true;
}

void UPropertyViewModel::Deinitialize()
{
	for (const auto& PropertyDependency : PropertyDependencyList)
	{
		PropertyDependency->OnPropertyChangedEvent.RemoveAll(this);
	}

	OnPropertyDeinitialized();
	bIsInitialized = false;
}

void UPropertyViewModel::HandleOnPropertyDependencyValueChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason)
{
	check(bIsInitialized)

	OnPropertyDependencyValueChanged(InPropertyViewModel, ChangedReason);
	OnPropertyValueChanged(EPropertyChangedReason::DependencyChanged);
	OnPropertyChangedEvent.Broadcast(this, EPropertyChangedReason::DependencyChanged);

	if (GetIsAutoApplyProperty())
	{
		Apply();
	}
}

void UPropertyViewModel::Startup()
{
	StartupComplete();
}

void UPropertyViewModel::StartupComplete()
{
	if (!bIsReady)
	{
		bIsReady = true;
		OnPropertyInitialized();
		OnPropertyReadyEvent.Broadcast(this);
	}
}

void UPropertyViewModel::Apply()
{
	check(bIsInitialized)

	if (CanApply())
	{
		bIsPropertyDirty = false;
		OnPropertyApply();
		OnPropertyApplyEvent.Broadcast(this);
	}
}

void UPropertyViewModel::Reset()
{
	check(bIsInitialized)

	if (CanReset())
	{
		bIsPropertyDirty = false;
		OnPropertyReset();
		OnPropertyResetEvent.Broadcast(this);
	}
}

void UPropertyViewModel::PrePropertyChanged()
{
	PrePropertyValueChanged();
}

void UPropertyViewModel::PostPropertyChanged()
{
	PostPropertyValueChanged();
}

void UPropertyViewModel::NotifyPropertyChanged(EPropertyChangedReason ChangedReason)
{
	check(bIsInitialized)

	if (!bIsPropertyDirty)
	{
		bIsPropertyDirty = true;

		if (GetIsAutoApplyProperty())
		{
			Apply();
		}

		OnPropertyChangedEvent.Broadcast(this, ChangedReason);
	}

	OnPropertyValueChanged(ChangedReason);
}

bool UPropertyViewModel::CanApply()
{
	return bIsPropertyDirty;
}

bool UPropertyViewModel::CanReset()
{
	return true;
}

UPropertyProxy* UPropertyViewModel::GetOwnerProxy() const
{
	return OwnerProxy;
}

bool UPropertyViewModel::GetIsInitialized() const
{
	return bIsInitialized;
}

bool UPropertyViewModel::GetIsReady() const
{
	return bIsReady;
}

bool UPropertyViewModel::GetIsPropertyValueDirty() const
{
	return bIsPropertyDirty;
}

bool UPropertyViewModel::GetIsAutoApplyProperty() const
{
	return IsAutoApplyProperty;
}

void UPropertyViewModel::SetIsAutoApplyProperty(const bool InIsAutoApplyProperty)
{
	if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(IsAutoApplyProperty, InIsAutoApplyProperty))
	{
		if (IsAutoApplyProperty && bIsPropertyDirty)
		{
			Apply();
		}
	}
}

bool UPropertyViewModel::GetIsDirtyProxy() const
{
	return IsDirtyProxy;
}

void UPropertyViewModel::SetIsDirtyProxy(bool InIsDirtyProxy)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(IsDirtyProxy, InIsDirtyProxy);
}

FName UPropertyViewModel::GetPropertyName() const
{
	return PropertyName;
}

void UPropertyViewModel::SetPropertyName(FName InPropertyName)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(PropertyName, InPropertyName);
}

const FText& UPropertyViewModel::GetPropertyDisplayName() const
{
	return PropertyDisplayName;
}

void UPropertyViewModel::SetPropertyDisplayName(const FText& InPropertyDisplayName)
{
	if (!PropertyDisplayName.EqualTo(InPropertyDisplayName))
	{
		PropertyDisplayName = InPropertyDisplayName;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDisplayName);
	}
}

const FText& UPropertyViewModel::GetPropertyDescription() const
{
	return PropertyDescription;
}

void UPropertyViewModel::SetPropertyDescription(const FText& InPropertyDescription)
{
	if (!PropertyDescription.EqualTo(InPropertyDescription))
	{
		PropertyDescription = InPropertyDescription;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDescription);
	}
}

void UPropertyViewModel::AddPropertyDependency(UPropertyViewModel* InPropertyDependency)
{
	if (!IsValid(InPropertyDependency))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDependency Is InValid"))
		return;
	}

	if (!PropertyDependencyList.Contains(InPropertyDependency))
	{
		return;
	}

	PropertyDependencyList.Add(InPropertyDependency);

	if (bIsInitialized)
	{
		OnPropertyDependencyAdded(InPropertyDependency);
		OnPropertyDependencyAddedEvent.Broadcast(InPropertyDependency);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDependencyList);
	}
}

void UPropertyViewModel::RemovePropertyDependency(UPropertyViewModel* InPropertyDependency)
{
	if (!IsValid(InPropertyDependency))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDependency Is InValid"))
		return;
	}

	if (!PropertyDependencyList.Contains(InPropertyDependency))
	{
		return;
	}

	PropertyDependencyList.Remove(InPropertyDependency);

	if (bIsInitialized)
	{
		OnPropertyDependencyRemoved(InPropertyDependency);
		OnPropertyDependencyRemovedEvent.Broadcast(InPropertyDependency);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDependencyList);
	}
}

void UPropertyViewModel::AddPropertyTag(FGameplayTag InPropertyTag)
{
	if (!InPropertyTag.IsValid())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyTag Is InValid"))
		return;
	}

	if (!InPropertyTag.MatchesTag(TAG_Property))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("This Tag Is Not a Property Tag"))
		return;
	}

	if (HasPropertyTag(InPropertyTag))
	{
		return;
	}

	PropertyTags.Add(InPropertyTag);

	if (bIsInitialized)
	{
		OnPropertyTagAdded(InPropertyTag);
		OnPropertyTagAddedEvent.Broadcast(this, InPropertyTag);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyTags);
	}
}

void UPropertyViewModel::RemovePropertyTag(FGameplayTag InPropertyTag)
{
	if (!InPropertyTag.IsValid())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyTag Is InValid"))
		return;
	}

	if (!InPropertyTag.MatchesTag(TAG_Property))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("This Tag Is Not a Property Tag"))
		return;
	}

	if (!HasPropertyTag(InPropertyTag))
	{
		return;
	}

	PropertyTags.Remove(InPropertyTag);

	if (bIsInitialized)
	{
		OnPropertyTagRemoved(InPropertyTag);
		OnPropertyTagRemovedEvent.Broadcast(this, InPropertyTag);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyTags);
	}
}

bool UPropertyViewModel::HasPropertyTag(FGameplayTag InPropertyTag) const
{
	return PropertyTags.Contains(InPropertyTag);
}

void UPropertyViewModel::OnPropertyInitialized()
{
	GenericLOG(GenericLogProperty, Log, TEXT("Initialized Property Name : %s"), *GetPropertyName().ToString());
}

void UPropertyViewModel::OnPropertyDeinitialized()
{
}

void UPropertyViewModel::OnPropertyApply()
{
}

void UPropertyViewModel::OnPropertyReset()
{
}

void UPropertyViewModel::OnPropertyDependencyAdded(UPropertyViewModel* InPropertyDependency)
{
}

void UPropertyViewModel::OnPropertyDependencyRemoved(UPropertyViewModel* InPropertyDependency)
{
}

void UPropertyViewModel::OnPropertyDependencyValueChanged(UPropertyViewModel* InDependencyProperty, EPropertyChangedReason ChangedReason)
{
}

void UPropertyViewModel::OnPropertyTagAdded(FGameplayTag InPropertyTag)
{
}

void UPropertyViewModel::OnPropertyTagRemoved(FGameplayTag InPropertyTag)
{
}

void UPropertyViewModel::PrePropertyValueChanged()
{
}

void UPropertyViewModel::PostPropertyValueChanged()
{
}

void UPropertyViewModel::OnPropertyValueChanged(EPropertyChangedReason ChangedReason)
{
}
