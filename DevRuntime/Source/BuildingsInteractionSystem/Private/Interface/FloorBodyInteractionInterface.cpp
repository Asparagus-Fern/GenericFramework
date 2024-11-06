// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/FloorBodyInteractionInterface.h"

void IFloorBodyInteractionInterface::NativeHandleFloorSelectionChanged(bool bIsSelected)
{
	bIsFloorSelected = bIsSelected;
	IFloorBodyInteractionInterface::Execute_HandleFloorSelectionChanged(Cast<UObject>(this), bIsSelected);
}
