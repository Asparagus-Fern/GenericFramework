// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/ButtonContainer_HorizontalBox.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UButtonContainer_HorizontalBox::OnChildAdded_Implementation(UUserWidget* InWidget, int32 InIndex)
{
	Super::OnChildAdded_Implementation(InWidget, InIndex);

	if (HorizontalBox_ButtonContainer)
	{
		UHorizontalBoxSlot* HorizontalBoxSlot = HorizontalBox_ButtonContainer->AddChildToHorizontalBox(InWidget);
		UpdateHorizontalBoxSlotPadding(HorizontalBoxSlot, InIndex);
	}
}

void UButtonContainer_HorizontalBox::OnChildRemoved_Implementation(UUserWidget* InWidget, int32 InIndex)
{
	Super::OnChildRemoved_Implementation(InWidget, InIndex);

	if (HorizontalBox_ButtonContainer)
	{
		HorizontalBox_ButtonContainer->RemoveChild(InWidget);
	}
}

void UButtonContainer_HorizontalBox::UpdateHorizontalBoxSlotPadding()
{
	if (HorizontalBox_ButtonContainer)
	{
		TArray<UWidget*> Widgets = HorizontalBox_ButtonContainer->GetAllChildren();
		for (int32 Index = 0; Index < Widgets.Num(); Index++)
		{
			UWidget* Widget = Widgets[Index];
			UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(Widget->Slot);
			UpdateHorizontalBoxSlotPadding(HorizontalBoxSlot, Index);
		}
	}
}

void UButtonContainer_HorizontalBox::UpdateHorizontalBoxSlotPadding(UHorizontalBoxSlot* InSlot, int32 InIndex)
{
	FMargin SlotPadding = ButtonPadding;
	SlotPadding.Left = (InIndex == 0) ? 0.f : SlotPadding.Left + ButtonSpacing;
	InSlot->SetPadding(SlotPadding);
}
