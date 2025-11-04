// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Interface/FloorBodyInteractionInterface.h"

void IFloorBodyInteractionInterface::NativeHandleFloorSelectionChanged(bool bIsSelected)
{
	bIsFloorSelected = bIsSelected;
	IFloorBodyInteractionInterface::Execute_HandleFloorSelectionChanged(Cast<UObject>(this), bIsSelected);
}
