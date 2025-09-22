// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/ButtonContainer/ButtonContainer_VerticalBox.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UButtonContainer_VerticalBox::OnChildAdded_Implementation(UGenericWidget* InWidget, int32 InIndex)
{
	Super::OnChildAdded_Implementation(InWidget, InIndex);

	if (VerticalBox_ButtonContainer)
	{
		UVerticalBoxSlot* VerticalBoxSlot = VerticalBox_ButtonContainer->AddChildToVerticalBox(InWidget);
		UpdateVerticalBoxSlotPadding(VerticalBoxSlot, InIndex);
	}
}

void UButtonContainer_VerticalBox::OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 InIndex)
{
	Super::OnChildRemoved_Implementation(InWidget, InIndex);

	if (VerticalBox_ButtonContainer)
	{
		VerticalBox_ButtonContainer->RemoveChild(InWidget);
	}
}

void UButtonContainer_VerticalBox::UpdateVerticalBoxSlotPadding()
{
	if (VerticalBox_ButtonContainer)
	{
		TArray<UWidget*> Widgets = VerticalBox_ButtonContainer->GetAllChildren();
		for (int32 Index = 0; Index < Widgets.Num(); Index++)
		{
			UWidget* Widget = Widgets[Index];
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(Widget->Slot);
			UpdateVerticalBoxSlotPadding(VerticalBoxSlot, Index);
		}
	}
}

void UButtonContainer_VerticalBox::UpdateVerticalBoxSlotPadding(UVerticalBoxSlot* InSlot, int32 SlotIndex)
{
	FMargin SlotPadding = ButtonPadding;
	SlotPadding.Top = (SlotIndex == 0) ? 0.f : SlotPadding.Top + ButtonSpacing;
	InSlot->SetPadding(SlotPadding);
}
