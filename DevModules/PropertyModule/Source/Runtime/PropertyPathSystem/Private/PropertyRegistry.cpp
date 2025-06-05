// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyRegistry.h"

#include "Base/PropertyEntity.h"
#include "Value/PropertyValueBase.h"

void UPropertyRegistry::ApplyPropertyChanges()
{
	if (!bPropertyChanged)
	{
		return;
	}

	for (auto& DirtyProperty : DirtyProperties)
	{
		if (UPropertyValueBase* PropertyValue = Cast<UPropertyValueBase>(DirtyProperty.Value))
		{
			PropertyValue->Apply();
			PropertyValue->StoreInitial();
		}
	}

	ClearDirtyState();
}

void UPropertyRegistry::SavePropertyChanges()
{
}

void UPropertyRegistry::RestoreToInitial()
{
	ensure(!bRestoringProperty);
	if (bRestoringProperty)
	{
		return;
	}

	TGuardValue<bool> LocalGuard(bRestoringProperty, true);
	for (auto& DirtyProperty : DirtyProperties)
	{
		if (UPropertyValueBase* PropertyValue = Cast<UPropertyValueBase>(DirtyProperty.Value))
		{
			PropertyValue->ResetToInitial();
		}
	}

	ClearDirtyState();
}

void UPropertyRegistry::ClearDirtyState()
{
	ensure(!bRestoringProperty);
	if (bRestoringProperty)
	{
		return;
	}

	bPropertyChanged = false;
	DirtyProperties.Reset();
}

void UPropertyRegistry::RegisterProperty(UPropertyEntity* InPropertyEntity)
{
	GenericEnsureLOG(PropertyLog, InPropertyEntity)

	if (InPropertyEntity)
	{
		TopLevelProperties.Add(InPropertyEntity);
		InPropertyEntity->SetOwningRegistry(this);
		RegisterInnerProperty(InPropertyEntity);
	}
}

void UPropertyRegistry::UnRegisterProperty(UPropertyEntity* InPropertyEntity)
{
	GenericEnsureLOG(PropertyLog, InPropertyEntity)

	if (InPropertyEntity)
	{
		if (TopLevelProperties.Contains(InPropertyEntity))
		{
			TopLevelProperties.Remove(InPropertyEntity);
		}

		UnRegisterInnerProperty(InPropertyEntity);
	}
}

void UPropertyRegistry::RegisterInnerProperty(UPropertyEntity* InPropertyEntity)
{
	GenericEnsureLOG(PropertyLog, InPropertyEntity)

	InPropertyEntity->OnPropertyChangedEvent.AddUObject(this, &ThisClass::HandlePropertyChanged);
	InPropertyEntity->OnPropertyAppliedEvent.AddUObject(this, &ThisClass::HandlePropertyApplied);
	InPropertyEntity->OnPropertyEditConditionChangedEvent.AddUObject(this, &ThisClass::HandlePropertyEditConditionsChanged);

	RegisteredProperties.Add(InPropertyEntity);

	for (const auto& ChildProperty : InPropertyEntity->GetChildProperties())
	{
		RegisterInnerProperty(ChildProperty);
	}
}

void UPropertyRegistry::UnRegisterInnerProperty(UPropertyEntity* InPropertyEntity)
{
	GenericEnsureLOG(PropertyLog, InPropertyEntity)

	for (const auto& ChildProperty : InPropertyEntity->GetChildProperties())
	{
		UnRegisterInnerProperty(ChildProperty);
	}

	InPropertyEntity->OnPropertyChangedEvent.RemoveAll(this);
	InPropertyEntity->OnPropertyAppliedEvent.RemoveAll(this);
	InPropertyEntity->OnPropertyEditConditionChangedEvent.RemoveAll(this);

	RegisteredProperties.Remove(InPropertyEntity);
}

void UPropertyRegistry::HandlePropertyChanged(UPropertyEntity* Property, EPropertyChangeReason Reason)
{
	if (!bRestoringProperty)
	{
		bPropertyChanged = true;
		DirtyProperties.Add(FObjectKey(Property), Property);

		if (GetIsAutoSaveProperty())
		{
			ApplyPropertyChanges();
			SavePropertyChanges();
		}
	}

	OnPropertyChanged(Property, Reason);
	OnPropertyChangedEvent.Broadcast(Property, Reason);
}

void UPropertyRegistry::HandlePropertyApplied(UPropertyEntity* Property)
{
	OnPropertyApplied(Property);
	OnPropertyAppliedEvent.Broadcast(Property);
}

void UPropertyRegistry::HandlePropertyEditConditionsChanged(UPropertyEntity* Property)
{
	OnPropertyEditConditionsChanged(Property);
	OnPropertyEditConditionsChangedEvent.Broadcast(Property);
}
