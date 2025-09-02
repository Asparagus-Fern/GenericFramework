// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ButtonContainer/ButtonContainer_HorizontalBox.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void UButtonContainer_HorizontalBox::OnChildAdded_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount)
{
	Super::OnChildAdded_Implementation(InWidget, NewChildrenCount);

	if (HorizontalBox_ButtonContainer)
	{
		HorizontalBox_ButtonContainer->AddChildToHorizontalBox(InWidget);
		UpdateHorizontalBoxSlotPadding();
	}
}

void UButtonContainer_HorizontalBox::OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount)
{
	Super::OnChildRemoved_Implementation(InWidget, NewChildrenCount);

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
		for (int32 i = 0; i < Widgets.Num(); i++)
		{
			UWidget* Widget = Widgets[i];
			UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(Widget->Slot);

			FMargin SlotPadding = ButtonPadding;
			SlotPadding.Right = (i == HorizontalBox_ButtonContainer->GetChildrenCount() - 1) ? 0.f : SlotPadding.Right + ButtonSpacing;

			HorizontalBoxSlot->SetPadding(SlotPadding);
		}
	}
}
