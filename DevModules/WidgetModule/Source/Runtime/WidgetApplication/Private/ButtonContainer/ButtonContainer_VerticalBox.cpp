// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ButtonContainer/ButtonContainer_VerticalBox.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UButtonContainer_VerticalBox::OnChildAdded_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount)
{
	Super::OnChildAdded_Implementation(InWidget, NewChildrenCount);

	if (VerticalBox_ButtonContainer)
	{
		VerticalBox_ButtonContainer->AddChildToVerticalBox(InWidget);
		UpdateVerticalBoxSlotPadding();
	}
}

void UButtonContainer_VerticalBox::OnChildRemoved_Implementation(UGenericWidget* InWidget, int32 NewChildrenCount)
{
	Super::OnChildRemoved_Implementation(InWidget, NewChildrenCount);

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
		for (int32 i = 0; i < Widgets.Num(); i++)
		{
			UWidget* Widget = Widgets[i];
			UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(Widget->Slot);

			FMargin SlotPadding = ButtonPadding;
			SlotPadding.Top = (i == 0) ? 0.f : SlotPadding.Top + ButtonSpacing;

			VerticalBoxSlot->SetPadding(SlotPadding);
		}
	}
}
