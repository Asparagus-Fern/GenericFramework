// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Widget/ListEntry/PropertyListEntry_Dynamic.h"

#include "Value/Scalar/PropertyScalarValue.h"

void UPropertyListEntry_Dynamic::SetPropertyEntity(UPropertyEntity* InProperty)
{
	Super::SetPropertyEntity(InProperty);
	BP_SetPropertyEntity();
}

void UPropertyListEntry_Dynamic::OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson)
{
	Super::OnPropertyChanged(InProperty, Reson);
	BP_OnPropertyChanged();
}

void UPropertyListEntry_Dynamic::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();
	BP_RefreshEditableState(bLocalIsEnabled);
}
