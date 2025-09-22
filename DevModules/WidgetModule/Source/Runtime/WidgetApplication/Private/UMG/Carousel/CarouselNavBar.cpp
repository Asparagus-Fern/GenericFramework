// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/Carousel/CarouselNavBar.h"

#include "GenericButtonWidget.h"
#include "UMG/Carousel/CarouselContent.h"

void UCarouselNavBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CarouselContent)
	{
		CarouselContent->SetNum(Num);
		CarouselContent->SetIndex(DefaultIndex);
	}
}

void UCarouselNavBar::NativeConstruct()
{
	Super::NativeConstruct();

	// if (Button_Left)
	// {
	// 	Button_Left->OnClicked.AddDynamic(this, &UCarouselNavBar::OnPreviewButtonClicked);
	// }
	//
	// if (Button_Right)
	// {
	// 	Button_Right->OnClicked.AddDynamic(this, &UCarouselNavBar::OnNextButtonClicked);
	// }

	if (CarouselContent)
	{
		CarouselContent->OnCarouselChanged.AddUObject(this, &UCarouselNavBar::HandleCarouselChanged);
	}
}

void UCarouselNavBar::NativeDestruct()
{
	Super::NativeDestruct();

	// if (Button_Left)
	// {
	// 	Button_Left->OnClicked.RemoveAll(this);
	// }
	//
	// if (Button_Right)
	// {
	// 	Button_Right->OnClicked.RemoveAll(this);
	// }

	if (CarouselContent)
	{
		CarouselContent->OnCarouselChanged.RemoveAll(this);
	}
}

void UCarouselNavBar::SetNum(int32 InNum)
{
	Num = InNum;

	if (CarouselContent)
	{
		CarouselContent->SetNum(InNum);
	}
}

void UCarouselNavBar::SetIndex(int32 InIndex)
{
	Index = InIndex;

	if (CarouselContent)
	{
		CarouselContent->SetIndex(InIndex);
	}

	OnCarouselIndexChanged.Broadcast(Index);
}

void UCarouselNavBar::OnPreviewButtonClicked(UGenericButtonWidget* InWidget)
{
	Index = (Index == 0) ? Num - 1 : Index - 1;
	SetIndex(Index);
}

void UCarouselNavBar::OnNextButtonClicked(UGenericButtonWidget* InWidget)
{
	Index = (Index == Num - 1) ? 0 : Index + 1;
	SetIndex(Index);
}

void UCarouselNavBar::HandleCarouselChanged(int32 InNum, int32 InIndex)
{
	Num = InNum;
	Index = InIndex;
}
