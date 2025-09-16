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
	}

	if (OnPropertyInitialized())
	{
		OnPropertyValueChanged(EPropertyChangedReason::Initialized);
		GenericLOG(GenericLogProperty, Log, TEXT("Initialized Property Name : %s"), *GetPropertyName().ToString());
		return true;
	}

	return false;
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

void UPropertyViewModel::Apply()
{
	check(bIsInitialized)
	
	if (CanApply())
	{
		NotifyPropertyChanged(EPropertyChangedReason::OnApply);
		OnPropertyApply();
		OnPropertyApplyEvent.Broadcast(this);
		bIsPropertyDirty = false;
	}
}

void UPropertyViewModel::Reverse()
{
	check(bIsInitialized)
	
	if (CanReverse())
	{
		OnPropertyReverse();
		OnPropertyReverseEvent.Broadcast(this);
		bIsPropertyDirty = false;
	}
}

void UPropertyViewModel::Reset()
{
	check(bIsInitialized)
	
	if (CanReset())
	{
		NotifyPropertyChanged(EPropertyChangedReason::OnReset);
		OnPropertyReset();
		OnPropertyResetEvent.Broadcast(this);
		bIsPropertyDirty = false;
	}
}

void UPropertyViewModel::NotifyPropertyChanged(EPropertyChangedReason ChangedReason)
{
	check(bIsInitialized)
	
	OnPropertyValueChanged(ChangedReason);

	if (!bIsPropertyDirty)
	{
		TGuardValue<bool> Guard(bIsPropertyDirty, true);

		if (GetIsAutoApplyProperty())
		{
			Apply();
		}

		OnPropertyChangedEvent.Broadcast(this, ChangedReason);
	}
}

bool UPropertyViewModel::CanApply()
{
	return bIsPropertyDirty;
}

bool UPropertyViewModel::CanReverse()
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

	if (PropertyDependencyList.Contains(InPropertyDependency))
	{
		return;
	}

	PropertyDependencyList.Add(InPropertyDependency);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDependencyList);
	OnPropertyDependencyAdded(InPropertyDependency);
	OnPropertyDependencyAddedEvent.Broadcast(InPropertyDependency);
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
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(PropertyDependencyList);
	OnPropertyDependencyRemoved(InPropertyDependency);
	OnPropertyDependencyRemovedEvent.Broadcast(InPropertyDependency);
}

bool UPropertyViewModel::OnPropertyInitialized()
{
	return true;
}

void UPropertyViewModel::OnPropertyDeinitialized()
{
}

void UPropertyViewModel::OnPropertyApply()
{
}

void UPropertyViewModel::OnPropertyReverse()
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

void UPropertyViewModel::OnPropertyValueChanged(EPropertyChangedReason ChangedReason)
{
}
