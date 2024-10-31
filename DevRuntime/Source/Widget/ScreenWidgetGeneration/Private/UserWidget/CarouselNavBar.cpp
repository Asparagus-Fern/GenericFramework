// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/CarouselNavBar.h"

#include "UserWidget/CarouselContent.h"
#include "UserWidget/Base/InteractableUserWidgetBase.h"

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

	if (Button_Left)
	{
		Button_Left->OnClicked.AddDynamic(this, &UCarouselNavBar::OnPreviewButtonClicked);
	}

	if (Button_Right)
	{
		Button_Right->OnClicked.AddDynamic(this, &UCarouselNavBar::OnNextButtonClicked);
	}

	if (CarouselContent)
	{
		CarouselContent->OnNumChanged.AddDynamic(this, &UCarouselNavBar::HandleNumChanged);
		CarouselContent->OnIndexChanged.AddDynamic(this, &UCarouselNavBar::UCarouselNavBar::HandleIndexChanged);
	}
}

void UCarouselNavBar::NativeDestruct()
{
	Super::NativeDestruct();

	if (Button_Left)
	{
		Button_Left->OnClicked.RemoveAll(this);
	}

	if (Button_Right)
	{
		Button_Right->OnClicked.RemoveAll(this);
	}

	if (CarouselContent)
	{
		CarouselContent->OnNumChanged.RemoveAll(this);
		CarouselContent->OnIndexChanged.RemoveAll(this);
	}
}

void UCarouselNavBar::OnPreviewButtonClicked(UInteractableUserWidgetBase* InWidget)
{
}

void UCarouselNavBar::OnNextButtonClicked(UInteractableUserWidgetBase* InWidget)
{
}

void UCarouselNavBar::HandleNumChanged(int32 InNum)
{
	Num = InNum;
}

void UCarouselNavBar::HandleIndexChanged(int32 InIndex)
{
	Index = InIndex;
}
