// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/PropertyEntity.h"

void UPropertyEntity::Initialize(ULocalPlayer* InLocalPlayer)
{
	if (LocalPlayer == InLocalPlayer)
	{
		return;
	}

	LocalPlayer = InLocalPlayer;

#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(PropertyName != NAME_None, TEXT("You Must Provide a PropertyName."));
	ensureAlwaysMsgf(!DisplayName.IsEmpty(), TEXT("You Must Provide a DisplayName."));
#endif

	for (const TSharedRef<FPropertyEditCondition>& EditCondition : EditConditions)
	{
		EditCondition->Initialize(LocalPlayer);
	}

	Startup();
}

FName UPropertyEntity::GetPropertyName() const
{
	return PropertyName;
}

void UPropertyEntity::SetPropertyName(const FName InPropertyName)
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

void UPropertyEntity::SetPropertyOwner(UPropertyEntity* InPropertyOwner)
{
	PropertyOwner = InPropertyOwner;
}

UPropertyEntity* UPropertyEntity::GetPropertyOwner() const
{
	return PropertyOwner;
}

void UPropertyEntity::AddEditCondition(const TSharedRef<FPropertyEditCondition>& InEditCondition)
{
	EditConditions.Add(InEditCondition);
	InEditCondition->OnEditConditionChangedEvent.AddUObject(this, &ThisClass::RefreshEditableState);
}

void UPropertyEntity::AddEditDependency(UPropertyEntity* DependencyPropertyEntity)
{
	if (ensure(DependencyPropertyEntity))
	{
		DependencyPropertyEntity->OnPropertyChangedEvent.AddUObject(this, &ThisClass::HandleEditDependencyChanged);
		DependencyPropertyEntity->OnPropertyEditConditionChangedEvent.AddUObject(this, &ThisClass::HandleEditDependencyChanged);
	}
}

void UPropertyEntity::Startup()
{
	StartupComplete();
}

void UPropertyEntity::StartupComplete()
{
	if (!bReady)
	{
		bReady = true;
		EditableStateCache = ComputeEditableState();

		OnInitialized();
	}
}

void UPropertyEntity::HandleEditDependencyChanged(UPropertyEntity* DependencySetting, EPropertyChangeReason Reason)
{
	OnDependencyChanged();
	RefreshEditableState();

	if (Reason != EPropertyChangeReason::DependencyChanged)
	{
		NotifySettingChanged(EPropertyChangeReason::DependencyChanged);
	}
}

void UPropertyEntity::HandleEditDependencyChanged(UPropertyEntity* DependencySetting)
{
	OnDependencyChanged();
	RefreshEditableState();
}

void UPropertyEntity::NotifySettingChanged(EPropertyChangeReason Reason)
{
	OnSettingChanged(Reason);

	for (const TSharedRef<FPropertyEditCondition>& EditCondition : EditConditions)
	{
		EditCondition->Changed(LocalPlayer, this, Reason);
	}

	if (!bOnPropertyChangedEventGuard)
	{
		TGuardValue<bool> Guard(bOnPropertyChangedEventGuard, true);
		OnPropertyChangedEvent.Broadcast(this, Reason);
	}
}

void UPropertyEntity::NotifyEditConditionsChanged()
{
	OnEditConditionsChanged();
	OnPropertyEditConditionChangedEvent.Broadcast(this);
}

FPropertyEditableState UPropertyEntity::ComputeEditableState() const
{
	FPropertyEditableState EditState;

	OnGatherEditState(EditState);

	for (const auto& EditCondition : EditConditions)
	{
		EditCondition->GatherEditState(LocalPlayer, EditState);
	}

	return EditState;
}

void UPropertyEntity::RefreshEditableState(bool bNotifyEditConditionsChanged)
{
	if (!LocalPlayer)
	{
		return;
	}

	if (!bOnEditConditionsChangedEventGuard)
	{
		TGuardValue<bool> Guard(bOnEditConditionsChangedEventGuard, true);

		EditableStateCache = ComputeEditableState();

		if (bNotifyEditConditionsChanged)
		{
			NotifyEditConditionsChanged();
		}
	}
}
