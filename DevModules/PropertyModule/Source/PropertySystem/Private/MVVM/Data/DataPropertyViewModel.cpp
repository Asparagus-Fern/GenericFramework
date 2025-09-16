// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "MVVM/Data/DataPropertyViewModel.h"

bool UDataPropertyViewModel::OnPropertyInitialized()
{
	bool Result = Super::OnPropertyInitialized();

	if (Result)
	{
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

void UDataPropertyViewModel::OnPropertyDeinitialized()
{
	Super::OnPropertyDeinitialized();
}

void UDataPropertyViewModel::OnPropertyApply()
{
	Super::OnPropertyApply();

	SetInitialValueFromString(GetCurrentValueAsString());
	PropertyDataSource->SetValueFromString(GetCurrentValueAsString());
}

void UDataPropertyViewModel::OnPropertyReverse()
{
	Super::OnPropertyReverse();

	SetCurrentValueFromString(GetInitialValueAsString());
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

UPropertyDataSource* UDataPropertyViewModel::GetPropertyDataSource()
{
	return PropertyDataSource;
}

void UDataPropertyViewModel::SetPropertyDataSource(UPropertyDataSource* InPropertyDataSource)
{
	if (!IsValid(InPropertyDataSource))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDataSource Is InValid"))
		return;
	}

	if (!InPropertyDataSource->Resolve())
	{
		GenericLOG(GenericLogProperty, Error, TEXT("PropertyDataSource Has a InValid Property Path"))
		return;
	}

	PropertyDataSource = InPropertyDataSource;

	SetInitialValueFromString(PropertyDataSource->GetValueAsString());
	SetCurrentValueFromString(PropertyDataSource->GetValueAsString());
}
