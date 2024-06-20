// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_CommonWidgetLayout.h"

#include "Components/ButtonSlot.h"
#include "Components/StackBoxSlot.h"
#include "Components/Widget.h"

UStackBoxSlot* UBPFunctions_CommonWidgetLayout::SlotAsStackBoxSlot(UWidget* Widget)
{
	if (Widget)
	{
		return Cast<UStackBoxSlot>(Widget->Slot);
	}

	return nullptr;
}

UButtonSlot* UBPFunctions_CommonWidgetLayout::SlotAsButtonSlot(UWidget* Widget)
{
	if (Widget)
	{
		return Cast<UButtonSlot>(Widget->Slot);
	}

	return nullptr;
}
