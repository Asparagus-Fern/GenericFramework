// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ButtonContainer/ButtonContainer_DynamicEntryBox.h"

#include "UWidget/GenericDynamicEntryBox.h"

void UButtonContainer_DynamicEntryBox::OnChildAdded_Implementation(UGenericWidget* InWidget, int32 InIndex)
{
	Super::OnChildAdded_Implementation(InWidget, InIndex);

	if (GenericDynamicEntryBox)
	{
		GenericDynamicEntryBox->AddEntry(InWidget);
	}
}

void UButtonContainer_DynamicEntryBox::OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 InIndex)
{
	Super::OnChildRemoved_Implementation(InWidget, InIndex);

	if (GenericDynamicEntryBox)
	{
		GenericDynamicEntryBox->RemoveEntry(InWidget);
	}
}
