// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/Carousel/CarouselContent.h"

void UCarouselContent::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetNum(5);
}

void UCarouselContent::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCarouselContent::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCarouselContent::SetNum(int32 InNum)
{
	Num = InNum;
	HandleOnCarouselChanged(Num, Index);
	OnCarouselChanged.Broadcast(Num, Index);
}

void UCarouselContent::SetIndex(int32 InIndex)
{
	Index = InIndex;
	HandleOnCarouselChanged(Num, Index);
	OnCarouselChanged.Broadcast(Num, Index);
}
