// Copyright ChenTaiye 2025. All Rights Reserved.


#include "MVVM/PropertyValueViewModel.h"

void UPropertyValueViewModel::Initialize_Implementation()
{
}

void UPropertyValueViewModel::Deinitialize_Implementation()
{
}

void UPropertyValueViewModel::Apply_Implementation()
{
	bIsPropertyDirty = false;
	// GetPropertySetter().ExecuteIfBound();
}

void UPropertyValueViewModel::Reverse_Implementation()
{
	bIsPropertyDirty = false;
}

void UPropertyValueViewModel::Reset_Implementation()
{
	bIsPropertyDirty = false;
}

bool UPropertyValueViewModel::GetIsPropertyDirty() const
{
	return bIsPropertyDirty;
}

void UPropertyValueViewModel::MarkAsPropertyDirty()
{
	bIsPropertyDirty = true;
}
