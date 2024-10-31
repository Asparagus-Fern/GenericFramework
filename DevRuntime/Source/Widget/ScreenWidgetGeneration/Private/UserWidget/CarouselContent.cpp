// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/CarouselContent.h"


void UCarouselContent::SetNum(int32 InNum)
{
	HandleOnNumChanged(InNum);
	OnNumChanged.Broadcast(InNum);
}

void UCarouselContent::SetIndex(int32 InIndex)
{
	HandleOnIndexChanged(InIndex);
	OnIndexChanged.Broadcast(InIndex);
}
