// Fill out your copyright notice in the Description page of Project Settings.


#include "FLoor/FloorStaticMeshComponent.h"

int32 UFloorStaticMeshComponent::GetFloor() const
{
	return Floor;
}

void UFloorStaticMeshComponent::SetFloor(const int32 InFloor)
{
	this->Floor = InFloor;
}
