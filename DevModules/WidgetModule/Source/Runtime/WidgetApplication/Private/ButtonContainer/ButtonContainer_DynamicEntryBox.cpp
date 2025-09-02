// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ButtonContainer/ButtonContainer_DynamicEntryBox.h"

#include "UWidget/GenericDynamicEntryBox.h"

void UButtonContainer_DynamicEntryBox::OnChildAdded_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount)
{
	Super::OnChildAdded_Implementation(InWidget, NewChildrenCount);

	if (GenericDynamicEntryBox_ButtonContainer)
	{
		GenericDynamicEntryBox_ButtonContainer->AddEntry(InWidget);
	}
}

void UButtonContainer_DynamicEntryBox::OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount)
{
	Super::OnChildRemoved_Implementation(InWidget, NewChildrenCount);

	if (GenericDynamicEntryBox_ButtonContainer)
	{
		GenericDynamicEntryBox_ButtonContainer->RemoveEntry(InWidget);
	}
}
