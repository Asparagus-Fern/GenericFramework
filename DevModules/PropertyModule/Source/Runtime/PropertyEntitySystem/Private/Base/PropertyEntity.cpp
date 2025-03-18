// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/PropertyEntity.h"

#include "Base/PropertyEditableState.h"
#include "Base/PropertyEditCondition.h"

void UPropertyEntity::Initialize(UObject* InSource, FName InPropertyName)
{
	if (!IsValid(InSource))
	{
		DLOG(DLogProperty, Error, TEXT("InSource Is InValid"))
		return;
	}

	if (InPropertyName == NAME_None)
	{
		DLOG(DLogProperty, Error, TEXT("InPropertyName Is InValid"))
		return;
	}

	if (bInitialize)
	{
		/* Property Is Initialized */
		return;
	}

	bInitialize = true;
	Source = InSource;
	PropertyName = InPropertyName;

	if (DisplayName.IsEmpty())
	{
		DisplayName = GetDefaultDisplayName();
	}

	if (DescriptionText.IsEmpty())
	{
		DescriptionText = GetDefaultDescriptionText();
	}

	/* Initialize Edit Condition. */
	for (const auto& EditCondition : EditConditions)
	{
		EditCondition->Initialize(Source);
		EditCondition->OnEditConditionChanged.AddUFunction(this, "RefreshEditableState", true);
	}

	Startup();
}

void UPropertyEntity::Startup()
{
	FinishStartup();
}

void UPropertyEntity::FinishStartup()
{
	if (!bReady)
	{
		bReady = true;
		ComputeEditableState();

		OnInitialized();
	}
}

void UPropertyEntity::OnInitialized()
{
	return;
}

FName UPropertyEntity::GetPropertyName() const
{
	return PropertyName;
}

void UPropertyEntity::SetPropertyName(FName InPropertyName)
{
	PropertyName = InPropertyName;
}

FText UPropertyEntity::GetDisplayName() const
{
	return DisplayName;
}

void UPropertyEntity::SetDisplayName(const FText& InDisplayName)
{
	DisplayName = InDisplayName;
}

FText UPropertyEntity::GetDescriptionText() const
{
	return DescriptionText;
}

void UPropertyEntity::SetDescriptionText(const FText& InDescriptionText)
{
	DescriptionText = InDescriptionText;
}

FText UPropertyEntity::GetDefaultDisplayName_Implementation()
{
	return FText::FromName(PropertyName);
}

FText UPropertyEntity::GetDefaultDescriptionText_Implementation()
{
	return FText::GetEmpty();
}

void UPropertyEntity::AddEditCondition(UPropertyEditCondition* InEditCondition)
{
	if (!EditConditions.Contains(InEditCondition))
	{
		EditConditions.Add(InEditCondition);
		InEditCondition->OnEditConditionChanged.AddUFunction(this, "RefreshEditableState", true);
	}
}

void UPropertyEntity::NotifyEditConditionsChanged()
{
	OnEditConditionsChanged();
	OnPropertyEditConditionChanged.Broadcast(this);
}

void UPropertyEntity::OnEditConditionsChanged_Implementation()
{
}

UPropertyEditableState* UPropertyEntity::GetEditableState()
{
	return EditableState;
}

void UPropertyEntity::RefreshEditableState(bool bNotifyEditConditionsChanged)
{
	if (!Source)
	{
		return;
	}

	if (!bOnEditConditionsChangedEventGuard)
	{
		TGuardValue<bool> Guard(bOnEditConditionsChangedEventGuard, true);

		ComputeEditableState();

		if (bNotifyEditConditionsChanged)
		{
			NotifyEditConditionsChanged();
		}
	}
}

void UPropertyEntity::ComputeEditableState()
{
	UPropertyEditableState* NewEditableState = NewObject<UPropertyEditableState>(this);
	OnGatherEditState(NewEditableState);

	for (const auto& EditCondition : EditConditions)
	{
		EditCondition->GatherEditState(Source, NewEditableState);
	}

	PostGatherEditState(NewEditableState);
	EditableState = NewEditableState;
}

void UPropertyEntity::OnGatherEditState_Implementation(UPropertyEditableState*& InOutEditState) const
{
}

void UPropertyEntity::PostGatherEditState_Implementation(UPropertyEditableState*& InOutEditState) const
{
}

void UPropertyEntity::AddPropertyDependency(UPropertyEntity* DependencyProperty)
{
	if (IsValid(DependencyProperty))
	{
		DependencyProperty->OnPropertyChangedEvent.AddUObject(this, &ThisClass::HandleDependencyPropertyChanged);
		DependencyProperty->OnPropertyEditConditionChanged.AddUObject(this, &ThisClass::HandleDependencyPropertyEditConditionChanged);
	}
}

void UPropertyEntity::HandleDependencyPropertyChanged(UPropertyEntity* DependencySetting, EPropertyChangeReason Reason)
{
	OnDependencyPropertyChanged();
	RefreshEditableState();

	if (Reason != EPropertyChangeReason::DependencyChanged)
	{
		NotifyPropertyChanged(EPropertyChangeReason::DependencyChanged);
	}
}

void UPropertyEntity::HandleDependencyPropertyEditConditionChanged(UPropertyEntity* DependencySetting)
{
	OnDependencyPropertyChanged();
	RefreshEditableState();
}

void UPropertyEntity::OnDependencyPropertyChanged_Implementation()
{
}

bool UPropertyEntity::IsSourceValid() const
{
	return IsValid(Source);
}

UPropertyEntity* UPropertyEntity::GetOwnerProperty() const
{
	return OwnerProperty;
}

void UPropertyEntity::SetOwnerProperty(UPropertyEntity* InOwnerProperty)
{
	OwnerProperty = InOwnerProperty;
}

UPropertyRegistry* UPropertyEntity::GetOwningRegistry() const
{
	return OwnerRegistry;
}

void UPropertyEntity::SetOwningRegistry(UPropertyRegistry* InOwnerRegistry)
{
	OwnerRegistry = InOwnerRegistry;
}

void UPropertyEntity::NotifyPropertyChanged(EPropertyChangeReason Reason)
{
	OnPropertyChanged(Reason);

	for (const auto& EditCondition : EditConditions)
	{
		EditCondition->Changed(Source, this, Reason);
	}

	if (!bOnPropertyChangedEventGuard)
	{
		TGuardValue<bool> Guard(bOnPropertyChangedEventGuard, true);
		OnPropertyChangedEvent.Broadcast(this, Reason);
	}
}

void UPropertyEntity::OnPropertyChanged_Implementation(EPropertyChangeReason Reason)
{
}

void UPropertyEntity::GetChildProperties_Implementation(TArray<UPropertyEntity*>& Children)
{
}
