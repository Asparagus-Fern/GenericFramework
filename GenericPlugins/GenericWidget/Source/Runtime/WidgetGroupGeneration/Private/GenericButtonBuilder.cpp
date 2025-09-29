// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonBuilder.h"

#include "GenericButtonContainer.h"
#include "GenericButtonGroup.h"
#include "MVVM/WidgetDescriptionViewModel.h"

UGenericButtonBuilder::UGenericButtonBuilder(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ButtonGroupClass = UGenericButtonGroup::StaticClass();
	WidgetDescriptionViewModel = CreateDefaultSubobject<UWidgetDescriptionViewModel>(TEXT("WidgetDescriptionViewModel"));
}
