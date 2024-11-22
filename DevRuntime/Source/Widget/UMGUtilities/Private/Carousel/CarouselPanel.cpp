// Fill out your copyright notice in the Description page of Project Settings.


#include "Carousel/CarouselPanel.h"

#include "CommonWidgetCarousel.h"
#include "Carousel/CarouselNavBar.h"

void UCarouselPanel::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CommonWidgetCarousel && CarouselNavBar)
	{
		CarouselNavBar->SetNum(CommonWidgetCarousel->GetChildrenCount());
		CarouselNavBar->SetIndex(CommonWidgetCarousel->GetActiveWidgetIndex());
	}
}

void UCarouselPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (CarouselNavBar)
	{
		CarouselNavBar->OnCarouselIndexChanged.AddUObject(this, &UCarouselPanel::HandleCarouselIndexChanged);
	}
}

void UCarouselPanel::NativeDestruct()
{
	Super::NativeDestruct();

	if (CarouselNavBar)
	{
		CarouselNavBar->OnCarouselIndexChanged.RemoveAll(this);
	}
}

void UCarouselPanel::HandleCarouselIndexChanged(int32 Index)
{
	if (CommonWidgetCarousel)
	{
		CommonWidgetCarousel->SetActiveWidgetIndex(Index);
	}
}
