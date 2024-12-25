// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/PropertyEntity.h"

#include "Debug/DebugType.h"

void UPropertyEntity::SetPropertyContext(UObject* InContext)
{
	Context = InContext;
}

void UPropertyEntity::Initialize()
{
	if (Context)
	{
		Initialize(Context);
	}
}

void UPropertyEntity::Initialize(UObject* InContext)
{
	/* 避免重复初始化 */
	DEnsureLOG(DLogProperty, !bInitialize)
	Context = InContext;
	bInitialize = true;

#if !UE_BUILD_SHIPPING
	DEnsureAlwaysLOG(DLogProperty, PropertyName != NAME_None, TEXT("You Must Provide a PropertyName."))
#endif

	/* 当DisplayName为空时，以PropertyName作为PropertyName */
	if (DisplayName.IsEmpty())
	{
		DisplayName = FText::FromName(PropertyName);
	}

	/* 初始化属性的编辑条件 */
	for (const auto& EditCondition : EditConditions)
	{
		EditCondition->Initialize(Context);
	}

	Startup();
}

void UPropertyEntity::Apply()
{
	OnApply();

	for (const auto& EditCondition : EditConditions)
	{
		EditCondition->Applied(Context, this);
	}

	OnPropertyAppliedEvent.Broadcast(this);
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

void UPropertyEntity::SetOwnerProperty(UPropertyEntity* InPropertyOwner)
{
	OwnerProperty = InPropertyOwner;
}

UPropertyEntity* UPropertyEntity::GetOwnerProperty() const
{
	return OwnerProperty;
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
		NotifyPropertyChanged(EPropertyChangeReason::DependencyChanged);
	}
}

void UPropertyEntity::HandleEditDependencyChanged(UPropertyEntity* DependencySetting)
{
	OnDependencyChanged();
	RefreshEditableState();
}

void UPropertyEntity::NotifyPropertyChanged(EPropertyChangeReason Reason)
{
	OnPropertyChanged(Reason);

	for (const TSharedRef<FPropertyEditCondition>& EditCondition : EditConditions)
	{
		EditCondition->Changed(Context, this, Reason);
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
		EditCondition->GatherEditState(Context, EditState);
	}

	return EditState;
}

void UPropertyEntity::RefreshEditableState(bool bNotifyEditConditionsChanged)
{
	if (!Context)
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
