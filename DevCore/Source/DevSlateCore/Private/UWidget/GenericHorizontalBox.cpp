// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "UWidget/GenericHorizontalBox.h"

#include "Components/HorizontalBoxSlot.h"

void UGenericHorizontalBox::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);

	if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(InSlot))
	{
		FMargin SlotPadding = HorizontalBoxSlot->GetPadding();
		SlotPadding.Left = (GetSlots().Num() == 1) ? 0.f : SlotPadding.Left + ButtonSpacing;
		HorizontalBoxSlot->SetPadding(SlotPadding);
	}
}

void UGenericHorizontalBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);
}
