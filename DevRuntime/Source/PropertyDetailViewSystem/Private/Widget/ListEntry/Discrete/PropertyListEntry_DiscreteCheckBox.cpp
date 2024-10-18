// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ListEntry/Discrete/PropertyListEntry_DiscreteCheckBox.h"

#include "Base/PropertyEditCondition.h"
#include "Components/CheckBox.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic.h"

void UPropertyListEntry_DiscreteCheckBox::SetPropertyEntity(UPropertyEntity* InProperty)
{
	Super::SetPropertyEntity(InProperty);
	
	Refresh();
}

void UPropertyListEntry_DiscreteCheckBox::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckBox_PropertyValue->OnCheckStateChanged.AddDynamic(this, &UPropertyListEntry_DiscreteCheckBox::OnCheckStateChanged);
}

void UPropertyListEntry_DiscreteCheckBox::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();
	CheckBox_PropertyValue->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_DiscreteCheckBox::OnCheckStateChanged(bool bIsCheck)
{
	DiscreteProperty->SetValueFromString(LexToString(bIsCheck));
}

void UPropertyListEntry_DiscreteCheckBox::Refresh()
{
	bool IsCheck;
	LexFromString(IsCheck, *DiscreteProperty->GetValueAsString());
	CheckBox_PropertyValue->SetIsChecked(IsCheck);
}
