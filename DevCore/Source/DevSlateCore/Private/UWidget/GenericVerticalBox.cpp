// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "UWidget/GenericVerticalBox.h"

#include "Components/VerticalBoxSlot.h"

void UGenericVerticalBox::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);

	if (UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(InSlot))
	{
		FMargin SlotPadding = VerticalBoxSlot->GetPadding();
		SlotPadding.Top = (GetSlots().Num() == 1) ? 0.f : SlotPadding.Top + ButtonSpacing;
		VerticalBoxSlot->SetPadding(SlotPadding);
	}
}

void UGenericVerticalBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);
}
