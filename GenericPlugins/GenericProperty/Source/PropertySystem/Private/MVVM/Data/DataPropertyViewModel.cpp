// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "MVVM/Data/DataPropertyViewModel.h"

#include "DataSource/PropertyDataSource.h"

UDataPropertyViewModel::UDataPropertyViewModel(const FObjectInitializer& FObjectInitializer)
	: Super(FObjectInitializer)
{
	PropertyOptionTags.Add(TAG_PropertyOption_Reset);
}

bool UDataPropertyViewModel::Initialize(UPropertyProxy* InOwnerProxy)
{
	bool Result = Super::Initialize(InOwnerProxy);

	if (Result)
	{
		if (!PropertyDataSource && !PropertyGetterPath.IsEmpty() && !PropertySetterPath.IsEmpty())
		{
			PropertyDataSource = UPropertyDataSource::Create(this, PropertyGetterPath, PropertySetterPath);
		}

		if (!PropertyDataSource)
		{
			GenericLOG(GenericLogProperty, Error, TEXT("Property Data Source Is InValid"))
			return false;
		}

		if (!PropertyDataSource->Resolve())
		{
			GenericLOG(GenericLogProperty, Error, TEXT("Property Data Source Resolve Fail, Check Is Valid Property Path."))
			return false;
		}

		SetInitialValueFromString(PropertyDataSource->GetValueAsString());
		SetCurrentValueFromString(PropertyDataSource->GetValueAsString());
	}

	return Result;
}

void UDataPropertyViewModel::Deinitialize()
{
	Super::Deinitialize();
}

void UDataPropertyViewModel::OnPropertyApply()
{
	Super::OnPropertyApply();

	SetInitialValueFromString(GetCurrentValueAsString());
	PropertyDataSource->SetValueFromString(GetCurrentValueAsString());
}

void UDataPropertyViewModel::OnPropertyReset()
{
	Super::OnPropertyReset();

	SetInitialValueFromString(PropertyDataSource->GetValueAsString());
	SetCurrentValueFromString(PropertyDataSource->GetValueAsString());
}

void UDataPropertyViewModel::OnPropertyDependencyValueChanged(UPropertyViewModel* InDependencyProperty, EPropertyChangedReason ChangedReason)
{
	Super::OnPropertyDependencyValueChanged(InDependencyProperty, ChangedReason);

	SetInitialValueFromString(PropertyDataSource->GetValueAsString());
	SetCurrentValueFromString(PropertyDataSource->GetValueAsString());
}

void UDataPropertyViewModel::OnPropertyValueChanged(EPropertyChangedReason ChangedReason)
{
	Super::OnPropertyValueChanged(ChangedReason);

	/* On Property Data Source Changed, Update View Model Data */
	if (ChangedReason == EPropertyChangedReason::Changed)
	{
		SetInitialValueFromString(PropertyDataSource->GetValueAsString());
		SetCurrentValueFromString(PropertyDataSource->GetValueAsString());
		Apply();
	}
	else if (ChangedReason == EPropertyChangedReason::UserInput)
	{
		/* If Choose The Initial Value, Reset This Property View Model */
		if (GetInitialValueAsString() == GetCurrentValueAsString())
		{
			Reset();
		}
	}
}

FString UDataPropertyViewModel::GetPropertyGetterPath() const
{
	return PropertyGetterPath;
}

void UDataPropertyViewModel::SetPropertyGetterPath(const FString& InPropertyGetterPath)
{
	if (InPropertyGetterPath.IsEmpty())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyGetterPath Is Empty"))
		return;
	}

	const FString GetterPath = InPropertyGetterPath;
	const FString SetterPath = PropertyDataSource->GetPropertySetterPath().ToString();

	UPropertyDataSource* NewDataSource = UPropertyDataSource::Create(this, GetterPath, SetterPath);
	if (SetPropertyDataSource(NewDataSource))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(PropertyGetterPath, InPropertyGetterPath);
	}
}

FString UDataPropertyViewModel::GetPropertySetterPath() const
{
	return PropertySetterPath;
}

void UDataPropertyViewModel::SetPropertySetterPath(const FString& InPropertySetterPath)
{
	if (InPropertySetterPath.IsEmpty())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertySetterPath Is Empty"))
		return;
	}

	const FString GetterPath = PropertyDataSource->GetPropertyGetterPath().ToString();
	const FString SetterPath = InPropertySetterPath;

	UPropertyDataSource* NewDataSource = UPropertyDataSource::Create(this, GetterPath, SetterPath);
	if (SetPropertyDataSource(NewDataSource))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(PropertySetterPath, InPropertySetterPath);
	}
}

UPropertyDataSource* UDataPropertyViewModel::GetPropertyDataSource()
{
	return PropertyDataSource;
}

bool UDataPropertyViewModel::SetPropertyDataSource(UPropertyDataSource* InPropertyDataSource)
{
	if (!IsValid(InPropertyDataSource))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDataSource Is InValid"))
		return false;
	}

	if (!InPropertyDataSource->Resolve())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDataSource Has a InValid Property Path"))
		return false;
	}

	PropertyDataSource = InPropertyDataSource;

	if (GetIsInitialized())
	{
		SetInitialValueFromString(PropertyDataSource->GetValueAsString());
		SetCurrentValueFromString(PropertyDataSource->GetValueAsString());
	}

	return true;
}
